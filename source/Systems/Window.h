#pragma once

// typedefs so we don't have to include glfw/glad
typedef unsigned int GLuint;
struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

enum class WindowState
{
	WindowedFullscreen = 1,
	Windowed = 2,
	Fullscreen = 3
};

// A window that everything will be rendered in
class Window
{
public:
	Window();
	~Window();

	// These static methods are so we can start opengl and shutdown opengl before we create windows
	static void start_opengl();
	static void shutdown_opengl();

	// If the window is still running
	bool running();

	// Update everything in the window and get dt
	double update();

	// Reset buffers inside the window
	void reset();

	// Swap the buffers to actually draw
	void swap_buffers();

	// Methods to swap to different window configs
	void update_state(const WindowState& s);
	void set_fullscreen();
	void set_windowed();
	void set_windowed_fullscreen();

private:
	// Members to describe the state of the window
	WindowState state;
	GLuint width, height;

	// Used to calculate dt
	double previous_time;

	// Actual pointer to the window we'll be using
	GLFWwindow* window;

	// Pointer to the monitor the window will be on
	GLFWmonitor* monitor;

	// Pointer to the video mode of the monitor
	const GLFWvidmode* monitor_video_mode;
};

