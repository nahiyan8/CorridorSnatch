#include <stdio.h>
#include <stdbool.h>

typedef struct
{
	bool sdl_video_initialised, sdl_audio_initialised;
	bool textures_loaded, sound_loaded;
} ENGINE_STATE; /* I'm so sorry :( */

#include "engine.c"

int main(int argc, char **argv) 
{	
	ENGINE_STATE engine_state = {false, false, false, false};
	
	if (initialise(&engine_state) != 0)
		quit(&engine_state);
	
	
	quit(&engine_state);
    return 0;
}
