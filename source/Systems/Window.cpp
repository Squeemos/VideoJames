#include "Window.h"
#include "../Errors.h"

#include "../Trace.h"
#include "InputManager.h"
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
static void resize_callback_function(GLFWwindow* glfw_window, int width, int height);

Window::Window() : fullscreen(false), width(1920), height(1080)
{
	trace_message("Creating Window");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	monitor = glfwGetPrimaryMonitor();

	window = glfwCreateWindow(width, height, "VideoJames", fullscreen ? monitor : nullptr, nullptr);
	if (!window)
	{
		throw EngineError(ErrorType::Window, "Error creating window.");
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback_function);
	glfwSetFramebufferSizeCallback(window, resize_callback_function);
	
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		throw EngineError(ErrorType::Window, "Error starting GLAD.");
	}

	glfwSwapInterval(0);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	previous_time = glfwGetTime();
	monitor_video_mode = glfwGetVideoMode(monitor);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
	trace_message("Destroying Window");
	glfwDestroyWindow(window);
}

bool Window::start_opengl()
{
	return glfwInit();
}

void Window::shutdown_opengl()
{
	glfwTerminate();
}

bool Window::running()
{
	return !glfwWindowShouldClose(window);
}

double Window::update()
{
	glfwPollEvents();

	double current = glfwGetTime();
	double dt = current - previous_time;
	previous_time = current;

	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_F))
	{
		fullscreen = !fullscreen;

		if (fullscreen)
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, width, height, monitor_video_mode->refreshRate);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, monitor_video_mode->refreshRate);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetWindowPos(window, 100, 100);
		}
	}

	return dt;
}

void Window::reset()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffers()
{
	glfwSwapBuffers(window);
}

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	scancode;
	action;
	mods;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(glfw_window, true);

	InputManager::get_instance().update_key(key, action);
}

static void resize_callback_function(GLFWwindow* glfw_window, int width, int height)
{
	glfw_window;
	glViewport(0, 0, width, height);
}