#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "linmath.h"

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Entity.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "Error.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <utility>
#include <map>
#include <sstream>
#include <string>

// Forward References
static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback_function(GLFWwindow* glfw_window, int window_width, int window_height);

// Initialize everything for the window
Window::Window() : fullscreen(false), red(0.0f), green(0.0f), blue(0.0f), width(1920), height(1080)
{
	std::cout << "Creating Window" << std::endl;

	// Set some window stuff (quality, resizable)
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Actually make the window
	window = glfwCreateWindow(width, height, "Title", NULL, NULL);
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
}

// Shutdown the window
Window::~Window()
{
	std::cout << "Destroying Window" << std::endl;
	// Once done, cleanup
	glfwDestroyWindow(window);
}

// Update the window
void Window::update(double dt)
{
	dt;

	// Update dt
	previous_time = current_time;

	// Exit the game
	if (check_key(GLFW_KEY_ESCAPE))
	{
		// Set the window to close
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		// Return since there's nothing we should try and draw
		return;
	}

	// Make fullscreen or take from fullscreen to windowed
	if (check_key(GLFW_KEY_F) == GLFW_PRESS)
	{
		// Get the video mode of the monitor
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		// Set the window to be fullscreen (currently uses monitor's resolution and refresh rate, can later be adjusted)
		if (!fullscreen)
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		// Set the window to be windowed (currently uses const resolution and monitor refresh rate, can later be adjusted)
		else
			glfwSetWindowMonitor(window, NULL, 0, 0, width, height, mode->refreshRate);

		fullscreen = !fullscreen;
	}

	// Check for input
	glfwPollEvents();

	// Update dt
	current_time = glfwGetTime();
}

void Window::reset()
{
	// Setup the buffer
	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT);
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

void Window::frambuffer_size_callback(GLFWwindow* glfw_window, int window_width, int window_height)
{
	glfw_window;
	// set the new height and width of the window
	glViewport(0, 0, window_width, window_height);
}

// Input handler
static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	mods;
	scancode;
	glfw_window;
	update_input(key, action);
}

static void framebuffer_size_callback_function(GLFWwindow* glfw_window, int window_width, int window_height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->frambuffer_size_callback(glfw_window, window_width, window_height);
}