#ifndef engine_h_defined
#define engine_h_defined

#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>

/*
 * Let me explain some of the data of the typical world, it has a unique ID, and a size. One will be randomly generated and
 * they have various doors to other worlds (to what worlds stored in *door_ids, where the doors are stored in *door_coords)
 * and the world is made out of various materials which have various textures with (positive & negative) resistances.
 *
 * World #0 is the menu screen.
 */

typedef struct
{
	uint64_t id;			SDL_Rect size;
	uint64_t *door_ids; 	SDL_Rect *door_coords;
	uint16_t **materials;	float resistance;
} world_t;

typedef struct
{
	uint64_t id, world_id;
	uint16_t type;
	SDL_Rect coord;
} entity_t;

typedef struct
{
	bool running;

	bool sdl_video_initialised, sdl_audio_initialised;

	bool textures_loaded, sounds_loaded;
	SDL_Surface *screen, **texture_materials, **texture_entities;

	uint64_t world_count, entity_count;
	world_t *worlds; entity_t *entities;
} engine_t;

engine_t engine_initialise(void);
void engine_main(engine_t engine);
void engine_quit(engine_t engine);

#endif
