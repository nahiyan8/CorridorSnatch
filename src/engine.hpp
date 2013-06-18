#ifndef engine_hpp_defined
#define engine_hpp_defined

#include <iostream>
#include <SDL/SDL.h>

typedef struct
	{ int16_t x, y; } coord_t;
	
typedef struct
	{ uint16_t w, h; } bounds_t;

 /*
 * Let me explain some of the data of the typical world, it has a unique ID, and a size. One will be randomly generated and
 * they have various doors to other worlds (to what worlds stored in *door_ids, where the doors are stored in *door_coords)
 * and the world is made out of various materials which have various textures with (positive & negative) resistances.
 *
 * If it's world 0, then it means that it's in the game menu.
 */

typedef struct
{
	uint16_t id;			bounds_t size;
	uint16_t *door_ids; 	SDL_Rect *door_coords;
	uint8_t **materials;	float resistance;
} map_t;

// Please keep each entity_t under 64 byte each and update the reading! THANK YOU!
// CURRENT: 42 bytes
typedef struct
{
	uint16_t type, map_id, animation_state, mass;
	float vel_x, vel_y, target_vel_x, target_vel_y;
	coord_t coord, crosshair;
	uint8_t opacity; bool collide;
} entity_t;

class GameEngine
{
	private:
		/*
		* running is just a bool saying whether the game is/should be running, sdl_*_initialised is a bool saying if SDL_Init has been
		* called on that successfully, *_loaded say if the * are loaded into memory from disk yet, *screen being the screen/window,
		* *buffer being the actual world rendered, and part of that is blitted onto *screen to simplify panning and stuff, **texture_*
		* being an array of SDL_Surface* with the index being the material/entity type,  world_count self-explanatory, world i.e. map
		* w/ additional data, *entity_count being the number of entities by type, entity_types being the number of types there are.
		* 
		* **texture_entities is too, an array of SDL_Surface*s, but each of them is not a simple image of them standing, no, it's like
		* a (horizontally) long surface with a lot of images, where the size of each image is stored in *texture_entity_size, and each
		* of them are an animation_state of the entity.
		* 
		* Note: material textures have the same size but not entities', so texture_entity_size is an array but texture_material_size is not.
		*/
		
		bool running;
		bool sdl_video_initialised, sdl_audio_initialised;
		bool textures_loaded, sounds_loaded;
		
		SDL_Surface *screen, *buffer; coord_t camera;
		uint32_t last_tick;
		
		SDL_Surface **texture_materials, **texture_entities; bounds_t texture_material_size, *texture_entity_size;
		map_t *maps; uint16_t map_count;
		entity_t *entities; uint16_t entity_count; uint8_t entity_types;
		
		SDLKey control_bindings[5]; // controls_map[MOVE_UP] = (SDLKey) SDLK_W; or something like that.
		
	public:
		GameEngine();
		~GameEngine();
		
		void main();
		
		void render_map(map_t *current_map, SDL_Surface **current_textures, bounds_t current_texture_size);
		void render_entities(map_t *current_map, SDL_Surface** current_textures, bounds_t *current_texture_size);
		
		void physics_update();
};

#define CONTROL_MOVELEFT	0
#define CONTROL_MOVERIGHT	1
#define CONTROL_MOVEUP		2
#define CONTROL_MOVEDOWN	3
#define CONTROL_PAUSE		4

#endif
