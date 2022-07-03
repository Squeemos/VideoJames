#include "Engine.h"

#include <iostream>

// Main
int main()
{
	engine_init();

	while (engine_is_running())
	{
		engine_update();
	}

	engine_shutdown();

	return 0;
}