#include "Engine.h"
#include "Systems/Window.h"
#include "Systems/Renderer.h"
#include "Systems/InputManager.h"

#include "Trace.h"

Engine::Engine()
{
	trace_message("Starting Engine");
	
	Window::start_opengl();

	__window = std::make_unique<Window>();
	__scene_manager = std::make_unique<SceneManager>();
	__renderer = std::make_unique<Renderer>();
}

Engine::~Engine()
{
	trace_message("Destroying Engine");

	Window::shutdown_opengl();
}

void Engine::run()
{
	while (__window->running())
	{
		__window->reset();

		InputManager::get_instance().update();

		double dt = __window->update();

		__scene_manager->update(dt);

		if (__scene_manager->shutdown())
			__window->close();

		__renderer->render(__scene_manager->get_renderables(), __scene_manager->get_camera());

		__window->swap_buffers();
	}
}
