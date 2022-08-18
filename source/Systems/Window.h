#pragma once

typedef unsigned int GLuint;
struct GLFWwindow;

class Window
{
public:
	Window();
	~Window();

	static bool start_opengl();
	static void shutdown_opengl();

	bool running();
	double update();
	void reset();
	void swap_buffers();

private:
	bool fullscreen;
	double previous_time;
	GLuint width, height;
	GLFWwindow* window;
};

