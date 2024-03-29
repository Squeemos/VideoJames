#pragma once

#include <memory>

class Window;
class Renderer;
class SceneManager;

// The game engine
class Engine
{
public:
	// Starts everything
	Engine();
	~Engine();

	// Runs the game
	void run();

private:
	// The members inside that interact
	std::unique_ptr<Window> __window;
	std::unique_ptr<SceneManager> __scene_manager;
	std::unique_ptr<Renderer> __renderer;
};

