#include "Engine.h"
#include "OpenGLHandler.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Trace.h"


// Start everything in the engine
GameEngine::GameEngine() : opengl_handler (std::make_unique<OpenGLHandler>()),
						   window(std::make_unique<Window>()),
	                       scene_manager(std::make_unique<SceneManager>())
{
	send_trace_message("Creating Engine");
}

// Shutdown everything in the engine
GameEngine::~GameEngine()
{
	send_trace_message("Destroying Engine");
}

// Update everything in the game engine
void GameEngine::update()
{
	double dt = window->get_dt();

	// Update
	scene_manager->update(dt, window->get_mouse());
	window->update(dt);

	// Empty buffers
	window->reset();

	// Draw everything in the scene
	scene_manager->draw();

	// Swap buffers
	window->swap_buffer();
}

// Check while the game engine is running
bool GameEngine::running()
{
	return window->running();
}