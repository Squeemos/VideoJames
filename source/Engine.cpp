#include "Engine.h"
#include "Systems/Window.h"
#include "Systems/SceneManager.h"
#include "Systems/Renderer.h"

#include "Trace.h"

Engine::Engine()
{
	trace_message("Starting Engine");
	
	if (!Window::start_opengl())
	{
		trace_message("Error starting opengl");
		std::abort();
	}

	window = std::make_unique<Window>();
	renderer = std::make_unique<Renderer>();
	scene_manager = std::make_unique<SceneManager>();
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

		scene_manager->update(dt);

		const auto& renderables = scene_manager->get_renderables();
		renderer->render(renderables);

		window->swap_buffers();
	}
}
