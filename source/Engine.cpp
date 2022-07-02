#include "Engine.h"
#include "Window.h"

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
	window_update();
}

// Shutdown everything in the engine
void engine_shutdown()
{
	window_shutdown();
}