#ifndef init_c_defined
#define init_c_defined

#include <stdio.h>
#include <SDL/SDL.h>
#include "errorlist.h"

int initialise(ENGINE_STATE& engine_state)
{
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		printf("(%s:%d:fatal): failed to initialise SDL_INIT_VIDEO\n", __FILE__, __LINE__);
		return ERROR_SDLINIT_VIDEO;
	}
	else
		engine_state.sdl_video_initialised = true;
	
	if ( SDL_InitSubSystem(SDL_INIT_AUDIO) == -1 )
	{
		printf("(%s:%d:warning): failed to initialise SDL_INIT_AUDIO\n", __FILE__, __LINE__);
		return ERROR_SDLINIT_AUDIO;
	}
	else
		engine_state.sdl_audio_initialised = true;
	
	
	
	return 0;
}

void quit(ENGINE_STATE& engine_state)
{
	if (engine_state.sdl_video_initialised || engine_state.sdl_audio_initialised)
		SDL_Quit();
}


#endif