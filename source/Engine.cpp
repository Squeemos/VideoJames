#include "Engine.h"
#include "Systems/Window.h"
#include "Systems/Renderer.h"
#include "Systems/InputManager.h"

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
	scene_manager = std::make_unique<SceneManager>();
	renderer = std::make_unique<Renderer>(scene_manager->get_camera());
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

		InputManager::get_instance().update();

		double dt = window->update();

		scene_manager->update(dt);

		if (scene_manager->scene_changed())
		{
			renderer->update_camera(scene_manager->get_camera());
			continue;
		}

		auto renderables = scene_manager->get_renderables();
		renderer->render(renderables);

		window->swap_buffers();
	}
}
