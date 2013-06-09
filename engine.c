#ifndef init_c_defined
#define init_c_defined

#include <iostream>
#include <SDL/SDL.h>
#include "errorlist.h"

int init(ENGINE_STATE& engine_state)
{
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		std::cout << '(' << __FILE__ << ':' << __LINE__ << ":fatal): failed to initialise SDL_INIT_VIDEO\n";
		return ERRORTYPE_SDLINIT_VIDEO;
	}
	else
		engine_state.sdl_video_initialised = true;
	
	if ( SDL_InitSubSystem(SDL_INIT_AUDIO) == -1 )
	{
		std::cout << '(' << __FILE__ << ':' << __LINE__ << ":warning): failed to initialise SDL_INIT_AUDIO\n";
		return ERRORTYPE_SDLINIT_AUDIO;
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