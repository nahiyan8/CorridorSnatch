#include "engine.h"

engine_t engine_initialise(void)
{
	engine_t engine;

	// Too many variables.. need more
	engine.sdl_video_initialised = false; engine.sdl_audio_initialised = false;
	engine.textures_loaded = false;       engine.sounds_loaded = false;
	engine.screen = NULL;                 engine.texture_materials = NULL;      engine.texture_entities = NULL;
	engine.world_count = 0;               engine.entity_count = 0;

	// Video is essential, so if it fails to load, exit.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("%s:%d: fatal: failed to initialise SDL_INIT_VIDEO: %s\n", __FILE__, __LINE__, SDL_GetError());
		return engine;
	}
	else
		engine.sdl_video_initialised = true;

	// Audio is non-essential!
	if ( SDL_InitSubSystem(SDL_INIT_AUDIO) < 0 )
		printf("%s:%d: warning: failed to initialise SDL_INIT_AUDIO: %s\n", __FILE__, __LINE__, SDL_GetError());
	else
		engine.sdl_audio_initialised = true;

	// Find the best video mode and make a screen like that.
	{
		SDL_Rect **screen_modes = SDL_ListModes(NULL, SDL_SWSURFACE);

		if ( screen_modes == NULL )
		{
			printf("%s:%d: fatal: failed to get a list of available screen modes: %s\n", __FILE__, __LINE__, SDL_GetError());
			return engine;
		}

		// If it's -1, it means any resolution can be used
		if ( screen_modes == (SDL_Rect**) -1 )
			engine.screen = SDL_SetVideoMode(1024, 600, 32, SDL_SWSURFACE);
		else
			engine.screen = SDL_SetVideoMode(screen_modes[0]->w, screen_modes[0]->h, 32, SDL_SWSURFACE);

		// Free the memory -- @fixme: makes a segfault
		//for (unsigned int slot = 0; screen_modes[slot]; slot++)
		//	free(screen_modes[slot]);
		//free(screen_modes);
	}

	engine.running = true;
	return engine;
}

void engine_main(engine_t engine)
{

}

void engine_quit(engine_t engine)
{
	if (engine.sdl_video_initialised || engine.sdl_audio_initialised)
		SDL_Quit();
}
