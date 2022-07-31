#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Error.h"
#include "Trace.h"

#include <iostream>
#include <memory>

// Main
int main()
{
	try
	{
		trace_init();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

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
		send_trace_message(e.what());
		trace_shutdown();
		return EXIT_FAILURE;
	}

	trace_shutdown();
	return EXIT_SUCCESS;
}