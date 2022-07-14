#pragma once
#include <memory>

class OpenGLHandler;
class Window;
class SceneManager;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void update();
	bool running();
private:
	std::unique_ptr<OpenGLHandler> opengl_handler;
	std::unique_ptr<Window> window;
	std::unique_ptr<SceneManager> scene_manager;
};