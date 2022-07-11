#include "Engine.h"

#include <iostream>
#include <memory>

// Figure out a way to make this exit a lot better

// Main
int main()
{
	std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>();

	while (engine->running())
	{
		engine->update();
	}

	return EXIT_SUCCESS;
}