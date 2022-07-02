#include "Engine.h"

#include <iostream>

// Main
int main()
{
	std::cout << "Engine init" << std::endl;
	engine_init();

	while (engine_is_running())
	{
		std::cout << "Engine update" << std::endl;
		engine_update();
	}

	std::cout << "Engine shutdown" << std::endl;
	engine_shutdown();

	return 0;
}