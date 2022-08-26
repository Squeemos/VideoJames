#pragma once

// typedefs so we don't have to include glfw/glad
typedef unsigned int GLuint;
struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

// A window that everything will be rendered in
class Window
{
public:
	Window();
	~Window();

	// These static methods are so we can start opengl and shutdown opengl before we create windows
	static bool start_opengl();
	static void shutdown_opengl();

	// If the window is still running
	bool running();

	// Update everything in the window and get dt
	double update();

	// Reset buffers inside the window
	void reset();

	// Swap the buffers to actually draw
	void swap_buffers();

private:
	// Members to describe the state of the window
	bool fullscreen;
	GLuint width, height;

	// Used to calculate dt
	double previous_time;

	// Actual pointer to the window we'll be using
	GLFWwindow* window;

	// Pointer to the monitor the window will be on
	GLFWmonitor* monitor;

	const GLFWvidmode* monitor_video_mode;
};

