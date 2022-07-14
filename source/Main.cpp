#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Error.h"

#include <iostream>
#include <memory>

// Main
int main()
{
	try
	{
		std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>();

		while (engine->running())
		{
			engine->update();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}