#include "Engine.h"
#include "OpenGLHandler.h"
#include "Window.h"
#include "Camera.h"

#include <iostream>
#include <memory>

// Start everything in the engine
GameEngine::GameEngine() : opengl_handler (std::make_unique<OpenGLHandler>()), window(std::make_unique<Window>()), camera(std::make_unique<Camera>())
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
	camera->update(dt);
	window->update(dt, *camera);
}

// Check while the game engine is running
bool GameEngine::running()
{
	return window->running();
}