#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Input.h"
#include "Error.h"
#include "Trace.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <utility>
#include <string>

// Forward References
static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback_function(GLFWwindow* glfw_window, int window_width, int window_height);
static void mouse_callback_function(GLFWwindow* glmfw_window, double x_pos, double y_pos);

// Initialize everything for the window
Window::Window() : fullscreen(false), red(0.0f), green(0.0f), blue(0.0f), width(1280), height(720), mouse(0.0f, 0.0f)
{
	send_trace_message("Creating Window");

	// Set some window stuff (quality, resizable)
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Actually make the window
	window = glfwCreateWindow(width, height, "VideoJames", NULL, NULL);
	if (!window)
	{
		throw WindowError();
	}

	// Setup for dt
	previous_time = glfwGetTime();
	current_time = glfwGetTime();

	// Set current context
	glfwMakeContextCurrent(window);

	// Update the user prointer of the window to this
	glfwSetWindowUserPointer(window, this);

	// Set the key callback function
	glfwSetKeyCallback(window, key_callback_function);

	// Set the resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_function);

	// Set the mouse callback function
	glfwSetCursorPosCallback(window, mouse_callback_function);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Load glad -> has to be done after glfwinit and window init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Destory window before exiting
		glfwDestroyWindow(window);
		throw GladError();
	}

	// Set the monitor to the primary one
	monitor = glfwGetPrimaryMonitor();

	// Set the buffer swap interval to 0 (no vsync) or 1 (vsync)
	glfwSwapInterval(0);
	// glfwSwapInterval(1);

	// global opengl states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Shutdown the window
Window::~Window()
{
	send_trace_message("Destroying Window");
	// Once done, cleanup
	glfwDestroyWindow(window);
}

// Update the window
void Window::update(double dt)
{
	dt;

	// Update dt
	previous_time = current_time;

	// Check for input
	glfwPollEvents();

	// Update dt
	current_time = glfwGetTime();
}

void Window::reset()
{
	// Setup the buffer
	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffer()
{
	// Swap the buffers to actually draw what we just loaded into them
	glfwSwapBuffers(window);
}

// Check to see if the window is still open
bool Window::running()
{
	return !glfwWindowShouldClose(window);
}

double Window::get_dt()
{
	return current_time - previous_time;
}

glm::vec2& Window::get_mouse()
{
	return mouse;
}

void Window::key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	scancode;
	mods;
	glfw_window;
	// Exit the game
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Set the window to close
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		// Return since there's nothing we should try and draw
		return;
	}

	// Make fullscreen or take from fullscreen to windowed
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		// Get the video mode of the monitor
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		// Set the window to be fullscreen (currently uses monitor's resolution and refresh rate, can later be adjusted)
		if (!fullscreen)
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		// Set the window to be windowed (currently uses const resolution and monitor refresh rate, can later be adjusted)
		else
		{
			glfwSetWindowMonitor(window, NULL, 0, 0, width, height, mode->refreshRate);

			// Set the position of the window to be in the center of the screen
			// This is really gross, find a way to fix it
			glfwSetWindowPos(window, static_cast<int>(static_cast<float>(mode->width) / 2.0f - (static_cast<float>(width) / 2.0f)), static_cast<int>(static_cast<float>(mode->height) / 2.0f - (static_cast<float>(height) / 2.0f)));
		}

		fullscreen = !fullscreen;
	}
}

void Window::frambuffer_size_callback(GLFWwindow* glfw_window, int window_width, int window_height)
{
	glfw_window;
	// set the new height and width of the window
	glViewport(0, 0, window_width, window_height);
}

void Window::mouse_callback(GLFWwindow* glfw_window, double x_pos, double y_pos)
{
	glfw_window;
	mouse.x = static_cast<float>(x_pos);
	mouse.y = static_cast<float>(y_pos);
}

// Input handler
static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	mods;
	scancode;
	glfw_window;
	update_input(key, action);

	static_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->key_callback(glfw_window, key, scancode, action, mods);
}

static void framebuffer_size_callback_function(GLFWwindow* glfw_window, int window_width, int window_height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->frambuffer_size_callback(glfw_window, window_width, window_height);
}

static void mouse_callback_function(GLFWwindow* glfw_window, double x_pos, double y_pos)
{
	static_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->mouse_callback(glfw_window, x_pos, y_pos);
}