#include "engine.h"

engine_t engine_initialise()
{
	engine_t engine_state = {false, false, false, false};
	
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
		printf("%s:%d: fatal: failed to initialise SDL_INIT_VIDEO\n", __FILE__, __LINE__);
	else
		engine_state.sdl_video_initialised = true;
	
	// Audio is non-essential!
	if ( SDL_InitSubSystem(SDL_INIT_AUDIO) == -1 )
		printf("%s:%d: warning: failed to initialise SDL_INIT_AUDIO\n", __FILE__, __LINE__);
	else
		engine_state.sdl_audio_initialised = true;
	
	return engine_state;
}

void engine_quit(engine_t engine_state)
{
	if (engine_state.sdl_video_initialised || engine_state.sdl_audio_initialised)
		SDL_Quit();
}