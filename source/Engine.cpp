#include "Engine.h"
#include "Window.h"

#include <iostream>

// Start everything in the engine
GameEngine::GameEngine() : window(new Window())
{
}

// Shutdown everything in the engine
GameEngine::~GameEngine()
{
	delete window;
}

// Update everything in the game engine
void GameEngine::update()
{
	double dt = window->get_dt();
	window->update(dt);
}

// Check while the game engine is running
bool GameEngine::running()
{
	return window->running();
}