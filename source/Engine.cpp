#include "Engine.h"
#include "Systems/Window.h"

#include "Trace.h"

Engine::Engine()
{
	trace_message("Starting Engine");
	
	if (!Window::start_opengl())
	{
		trace_message("Error starting opengl");
		std::abort();
	}

	window = std::make_shared<Window>();
}

Engine::~Engine()
{
	trace_message("Destroying Engine");

	Window::shutdown_opengl();
}

void Engine::run()
{
	while (window->running())
	{
		window->reset();
		double dt = window->update();

		dt;

		window->swap_buffers();
	}
}
