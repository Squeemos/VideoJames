#include "Engine.h"
#include "OpenGLHandler.h"
#include "Window.h"
#include "SceneManager.h"
#include "Camera.h"

#include <iostream>

// Start everything in the engine
GameEngine::GameEngine() : opengl_handler (std::make_unique<OpenGLHandler>()),
						   window(std::make_unique<Window>()),
	                       scene_manager(std::make_unique<SceneManager>())
{
	std::cout << "Creating Engine" << std::endl;
}

// Shutdown everything in the engine
GameEngine::~GameEngine()
{
	std::cout << "Destroying Engine" << std::endl;
}

// Update everything in the game engine
void GameEngine::update()
{
	double dt = window->get_dt();

	// Update
	scene_manager->update(dt);
	window->update(dt);

	// Draw
	window->reset();

	scene_manager->draw();

	window->swap_buffer();
}

// Check while the game engine is running
bool GameEngine::running()
{
	return window->running();
}