#pragma once

class OpenGLHandler;
class Window;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void update();
	bool running();
private:
	OpenGLHandler* opengl_handler;
	Window* window;
};