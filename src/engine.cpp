#include "engine.hpp"

GameEngine::GameEngine()
{
	// Too many variables.. need more
	running = false;
	sdl_video_initialised = false; sdl_audio_initialised = false;
	textures_loaded = false; sounds_loaded = false;
	
	screen = NULL; buffer = NULL; camera.x = 0; camera.y = 0;
	last_tick = 0xDEADBEEF;
	
	texture_materials = NULL; texture_entities = NULL; texture_material_size = {0xBEEF, 0xBEEF}; texture_entity_size = NULL;
	entities = NULL; entity_count = 0; entity_types = 0;
	maps = NULL; map_count = 0;

	// Video is essential, so if it fails to load, exit.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		std::cout << __FILE__ << ':' << __LINE__ << ": fatal: failed to initialise SDL_INIT_VIDEO: " << SDL_GetError() << '\n';
		return;
	}
	else
		sdl_video_initialised = true;

	// Audio is non-essential!
	if ( SDL_InitSubSystem(SDL_INIT_AUDIO) < 0 )
		std::cout << __FILE__ << ':' << __LINE__ << ": warning: failed to initialise SDL_INIT_AUDIO: " << SDL_GetError() << '\n';
	else
		sdl_audio_initialised = true;

	// Find the best video mode and make a screen like that.
	{
		SDL_Rect **screen_modes = SDL_ListModes(NULL, SDL_SWSURFACE);

		if ( screen_modes == NULL )
		{
			std::cout << __FILE__ << ':' << __LINE__ << ": fatal: failed to get a list of available screen modes: " << SDL_GetError() << '\n';
			return;
		}

		// If it's -1, it means any resolution can be used
		if ( screen_modes == (SDL_Rect**) -1 )
			screen = SDL_SetVideoMode(1024, 600, 32, SDL_SWSURFACE);
		else
		{
			screen = SDL_SetVideoMode(screen_modes[0]->w, screen_modes[0]->h, 32, SDL_SWSURFACE);

			// Free the memory -- @fixme: makes a segfault
			//for (unsigned int slot = 0; screen_modes[slot]; slot++)
			//	free(screen_modes[slot]);
			//free(screen_modes);
		}
	}

	// Load textures from file names in the form of *.png, and load them up alphabetically into the array.
	// End loading textures
	
	// Load up sounds!
	
	running = true;
}

GameEngine::~GameEngine()
{
	if (sdl_video_initialised || sdl_audio_initialised)
		SDL_Quit();
}

void GameEngine::main()
{
	SDL_Event event;
	map_t *current_map;
	SDL_Rect camera_blit_coord;
	
	// Main loop
	while (running)
	{
		// Handle events!
		while ( SDL_PollEvent(&event) )
			switch (event.type)
			{
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == control_bindings[CONTROL_MOVELEFT])		entities[0].accel_x = -1;	break;
					if (event.key.keysym.sym == control_bindings[CONTROL_MOVERIGHT])	entities[0].accel_x = 1;	break;
					if (event.key.keysym.sym == control_bindings[CONTROL_MOVEUP])		entities[0].accel_y = -1;	break;
					if (event.key.keysym.sym == control_bindings[CONTROL_MOVEDOWN])		entities[0].accel_y = 1;	break;
				}
				
				case SDL_MOUSEMOTION:
				{
					entities[0].crosshair.x = event.motion.x;
					entities[0].crosshair.y = event.motion.y;
					break;
				}
			}
			
//		physics_update();
		
		current_map = maps + entities[0].map_id;
		render_map(current_map, texture_materials, texture_material_size);
		render_entities(current_map, texture_entities, texture_entity_size);
		
		camera_blit_coord.x = camera.x; camera_blit_coord.y = camera.y;
		camera_blit_coord.w = screen->w; camera_blit_coord.h = screen->h;
		
		SDL_BlitSurface(buffer, &camera_blit_coord, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
	}
}

void GameEngine::render_map(map_t *current_map, SDL_Surface **current_textures, bounds_t current_texture_size)
{
	uint32_t slot_x = 0, slot_y = 0; SDL_Rect blit_coord = {0, 0, (Uint16) current_texture_size.w, (Uint16) current_texture_size.h};

	for ( ; slot_x < current_map->size.w; slot_x++, blit_coord.x += current_texture_size.w )
		for ( ; slot_y < current_map->size.h; slot_y++, blit_coord.y += current_texture_size.h )
		{
			// current_map->materials[slot_x][slot_y] is the material type, and the textures for materials are at
			// texture_materials[material_type]. NULL meaning blit the whole image from source, buffer is to where,
			// and blit_coord is the location, and size of the blit.
			SDL_BlitSurface( current_textures[ current_map->materials[slot_x][slot_y] ], NULL, buffer, &blit_coord );
		}

	/*
	* Example ASCII dude:
	* -------------------------------
	* |  o  |__o  | \o  |  o__|  o/ |
	* | /|\ |  |\ |  |\ | /|  | /|  |
	* | / \ | / \ | / \ | / \ | / \ |
	* -------------------------------
	* 
	* As you can see (read: decipher; monospace font easiest/only way), the frames are:
	*  1. Dude standing still
	*  2. Dude in the middle of an animation, him in the middle of lifting his hand up
	*  3. Dude waving his left hand.
	*  4. Like 3 but with the right hand instead.
	*  5. Waving his right hand.. hey.. is he giving me the finger?!
	* 
	* As you can see, an animation can be many different things, it basically is just a different image for it, to show it doing stuff.
	* You can even make a button that's an entity and change its animation_state when it's hovered over and when it's clicked!
	*/
}

void GameEngine::render_entities(map_t *current_map, SDL_Surface** current_textures, bounds_t *current_texture_size)
{
	uint32_t slot = 0; SDL_Rect blit_src_coord, blit_dest_coord;
	
	for ( ; slot < entity_count; slot++ )
	{
		// Skip if this entity is not in the current_map
		if ( entities[slot].map_id != current_map->id )
			continue;
		
		blit_src_coord.w = texture_entity_size[entities[slot].type].w;
		blit_src_coord.h = texture_entity_size[entities[slot].type].h;
		
		// The actual image is like a really (horizontally) long picture split up into frames of animation per offset of texture_entity_size
		blit_src_coord.x = texture_entity_size[entities[slot].type].w * entities[slot].animation_state;
		blit_src_coord.y = 0;
		
		blit_dest_coord.w = texture_entity_size[entities[slot].type].w;
		blit_dest_coord.h = texture_entity_size[entities[slot].type].h;
		blit_dest_coord.x = entities[slot].coord.x;
		blit_dest_coord.y = entities[slot].coord.y;
		
		SDL_BlitSurface( texture_entities[entities[slot].type], &blit_src_coord, buffer, &blit_dest_coord );
	}
}
/*
void GameEngine::physics_update()
{
	// Update entity speeds/positions!
	for (uint32_t slot = 0; slot < entity_count; slot++)
	{
		entities[slot].vel_x = (entities[slot].vel_x + entities[slot].target_vel_x) / 2.0f;
		entities[slot].vel_y = (entities[slot].vel_y + entities[slot].target_vel_y) / 2.0f;
	}	
}*/