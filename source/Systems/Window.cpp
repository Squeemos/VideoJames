#include "Window.h"
#include "../Errors.h"

#include "../Trace.h"
#include "InputManager.h"
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
static void resize_callback_function(GLFWwindow* glfw_window, int width, int height);

Window::Window() : state(WindowState::Windowed), width(1920), height(1080)
{
	trace_message("Creating Window");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	monitor = glfwGetPrimaryMonitor();

	window = glfwCreateWindow(width, height, "VideoJames", (state == WindowState::Fullscreen) ? monitor : nullptr, nullptr);
	if (!window)
	{
		throw EngineError(ErrorType::Window, "Error creating window");
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback_function);
	glfwSetFramebufferSizeCallback(window, resize_callback_function);
	
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		throw EngineError(ErrorType::Window, "Error starting GLAD");
	}

	glfwSwapInterval(0);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	previous_time = glfwGetTime();
	monitor_video_mode = glfwGetVideoMode(monitor);

	update_state(state);
}

Window::~Window()
{
	trace_message("Destroying Window");
	glfwDestroyWindow(window);
}

void Window::start_opengl()
{
	if (!glfwInit())
	{
		throw EngineError(ErrorType::Window, "Failed to start OpenGL");
	}
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

void Window::update_state(const WindowState& s)
{
	state = s;
	switch (s)
	{
	case WindowState::WindowedFullscreen:
		set_windowed_fullscreen();
		break;
	case WindowState::Windowed:
		set_windowed();
		break;
	case WindowState::Fullscreen:
		set_fullscreen();
		break;
	default:
		break;
	}
}

void Window::set_fullscreen()
{
	glfwSetWindowMonitor(window, monitor, 0, 0, width, height, monitor_video_mode->refreshRate);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::set_windowed()
{
	glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, monitor_video_mode->refreshRate);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowPos(window, 100, 100);
}

void Window::set_windowed_fullscreen()
{
	glfwSetWindowMonitor(window, nullptr, 0, 0, monitor_video_mode->width, monitor_video_mode->height, monitor_video_mode->refreshRate);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowPos(window, 0, 0);
}

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	scancode;
	action;
	mods;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(glfw_window, true);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::Fullscreen);
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
		reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::WindowedFullscreen);
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
		reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::Windowed);

	InputManager::get_instance().update_key(key, action);
}

static void resize_callback_function(GLFWwindow* glfw_window, int width, int height)
{
	glfw_window;
	glViewport(0, 0, width, height);
}