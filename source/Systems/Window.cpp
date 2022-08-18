#include "Window.h"

#include "../Trace.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);

Window::Window() : fullscreen(false), width(1280), height(720)
{
	trace_message("Creating Window");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "VideoJames", nullptr, nullptr);
	if (!window)
	{
		trace_message("Error creating window.");
		std::abort();
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback_function);
	
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		trace_message("Error starting glad");
		glfwDestroyWindow(window);
		glfwTerminate();
		std::abort();
	}

	glfwSwapInterval(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	return 0.0;
}

void Window::reset()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
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
}