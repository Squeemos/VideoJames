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
	scene_manager->update(dt);
	window->draw(*scene_manager->get_current_scene());
	window->update(dt);
}

// Check while the game engine is running
bool GameEngine::running()
{
	return window->running();
}