#include "Engine.h"

#include <iostream>
#include <signal.h> // Figure out this to make exiting proper

// Main
int main()
{
	GameEngine* engine = new GameEngine();

	while (engine->running())
	{
		engine->update();
	}

	delete engine;

	return EXIT_SUCCESS;
}