#include <stdio.h>
#include <stdbool.h>

#include "engine.h"

int main(int argc, char **argv) 
{	
	// Declarations
	engine_t engine;
	
	// Initialisation
	engine = engine_initialise();
	
	// Main
	SDL_Delay(10000);
	
	// Exit
	engine_quit(engine);
	return 0;
}