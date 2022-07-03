#pragma once

typedef struct GLFWwindow GLFWwindow;
typedef struct GLFWmonitor GLFWmonitor;

class Window
{
public:
	Window();
	~Window();
	bool running();
	void update(double dt);
	double get_dt();
	void draw();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	double previous_time;
	bool fullscreen;
};