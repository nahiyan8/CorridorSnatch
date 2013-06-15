#include <stdio.h>
#include <stdbool.h>

#include "engine.h"

int main(int argc, char **argv) 
{	
	// Declarations
	engine_t engine_state;
	
	// Initialisation
	engine_state = engine_initialise();
	
	// Main
	SDL_Delay(10000);
	
	// Exit
	engine_quit(engine_state);
	return 0;
}
