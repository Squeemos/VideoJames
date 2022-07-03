#include "Engine.h"

#include <iostream>

// Main
int main()
{
	GameEngine* engine = new GameEngine();

	while (engine->running())
	{
		engine->update();
	}

	delete engine;

	return 0;
}