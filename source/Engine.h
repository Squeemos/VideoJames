#pragma once

class Window;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void update();
	bool running();
private:
	Window* window;
};