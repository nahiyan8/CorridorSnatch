#ifndef engine_h_defined
#define engine_h_defined

typedef struct
{
	bool sdl_video_initialised, sdl_audio_initialised;
	bool textures_loaded, sound_loaded;
} engine_t;

engine_t engine_initialise();
void engine_quit(engine_t engine_state);

#include "engine.c"

#endif