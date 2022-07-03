#include "Engine.h"
#include "Window.h"

#include <iostream>

// Whether to keep updating the engine
bool engine_is_running()
{
	return window_is_running();
}

// Start everything in the engine
void engine_init()
{
	window_init();
}

// Update everything in the engine
void engine_update()
{
	double dt = get_dt();
	window_update(dt);
}

// Shutdown everything in the engine
void engine_shutdown()
{
	window_shutdown();
}