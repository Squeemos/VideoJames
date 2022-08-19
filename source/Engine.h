#pragma once

#include <memory>

class Window;
class Renderer;
class SceneManager;

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	std::unique_ptr<Window> window;
	std::unique_ptr<SceneManager> scene_manager;
	std::unique_ptr<Renderer> renderer;
};

