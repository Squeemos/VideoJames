#pragma once

#include <memory>

class Window;

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	std::shared_ptr<Window> window;
};

