#include "Engine.h"
#include "Window.h"

#include <iostream>

// Start everything in the engine
GameEngine::GameEngine()
{
	window_init();
}

// Shutdown everything in the engine
GameEngine::~GameEngine()
{
	window_shutdown();
}

void GameEngine::update()
{
	double dt = get_dt();
	window_update(dt);
}

bool GameEngine::running()
{
	return window_is_running();
}