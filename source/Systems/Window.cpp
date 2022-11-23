#include "Window.h"
#include "../Errors.h"

#include "../Trace.h"
#include "InputManager.h"
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
static void resize_callback_function(GLFWwindow* glfw_window, int width, int height);
static void mouse_callback_function(GLFWwindow* glfw_window, double x, double y);
static void mouse_click_callback_function(GLFWwindow* glfw_window, int button, int action, int mods);

Window::Window() : __state(WindowState::Windowed), __width(1920), __height(1080), __current_width(1920), __current_height(1080)
{
	trace_message("Creating Window");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	__monitor = glfwGetPrimaryMonitor();

	__window = glfwCreateWindow(__width, __height, "VideoJames", (__state == WindowState::Fullscreen) ? __monitor : nullptr, nullptr);
	if (!__window)
	{
		throw EngineError(ErrorType::Window, "Error creating window");
	}

	glfwMakeContextCurrent(__window);
	glfwSetWindowUserPointer(__window, this);
	glfwSetKeyCallback(__window, key_callback_function);
	glfwSetFramebufferSizeCallback(__window, resize_callback_function);
	glfwSetCursorPosCallback(__window, mouse_callback_function);
	glfwSetMouseButtonCallback(__window, mouse_click_callback_function);
	
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwDestroyWindow(__window);
		glfwTerminate();
		throw EngineError(ErrorType::Window, "Error starting GLAD");
	}

	glfwSwapInterval(0);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	__previous_time = glfwGetTime();
	__monitor_video_mode = glfwGetVideoMode(__monitor);

	update_state(__state);
}

Window::~Window()
{
	trace_message("Destroying Window");
	glfwDestroyWindow(__window);
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
	return !glfwWindowShouldClose(__window);
}

double Window::update()
{
	glfwPollEvents();

	double current = glfwGetTime();
	double dt = current - __previous_time;
	__previous_time = current;

	return dt;
}

void Window::reset()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close()
{
	glfwSetWindowShouldClose(__window, true);
}

void Window::swap_buffers()
{
	glfwSwapBuffers(__window);
}

void Window::update_state(const WindowState& s)
{
	__state = s;
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
		trace_message("Unhandled WindowState...");
		break;
	}
}

void Window::set_fullscreen()
{
	glfwSetWindowMonitor(__window, __monitor, 0, 0, __width, __height, __monitor_video_mode->refreshRate);
	glfwSetInputMode(__window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::set_windowed()
{
	glfwSetWindowMonitor(__window, nullptr, 0, 0, __width, __height, __monitor_video_mode->refreshRate);
	__current_width = __width;
	__current_height = __height;
	glfwSetInputMode(__window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowPos(__window, 100, 100);
}

void Window::set_windowed_fullscreen()
{
	glfwSetWindowMonitor(__window, nullptr, 0, 0, __monitor_video_mode->width, __monitor_video_mode->height, __monitor_video_mode->refreshRate);
	__current_width = __monitor_video_mode->width;
	__current_height = __monitor_video_mode->height;
	glfwSetInputMode(__window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowPos(__window, 0, 0);
}

std::pair<double, double> Window::screen_coordinates(double x, double y) const
{
	double new_x = x / static_cast<double>(__current_width);
	double new_y = 1 - y / static_cast<double>(__current_height);
	return std::pair<double, double>(new_x, new_y);
}

static void key_callback_function(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
	scancode;

	if ((mods & GLFW_KEY_LEFT_ALT || mods & GLFW_KEY_RIGHT_ALT) && key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		WindowState current_state = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->get_current_state();
		if (current_state == WindowState::Fullscreen)
			reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::Windowed);
		else if (current_state == WindowState::WindowedFullscreen)
			reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::Windowed);
		else if (current_state == WindowState::Windowed)
			reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->update_state(WindowState::Fullscreen);
		else
			trace_message("Problem trying to change the __window using ALT+ENTER...");
	}
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

static void mouse_callback_function(GLFWwindow* glfw_window, double x, double y)
{
	glfw_window;
	std::pair<double, double> mouse_pos = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window))->screen_coordinates(x, y);
	InputManager::get_instance().update_mouse_position(mouse_pos);
}

static void mouse_click_callback_function(GLFWwindow* glfw_window, int button, int action, int mods)
{
	glfw_window;
	mods;
	InputManager::get_instance().update_mouse_click(button, action);
}

WindowState Window::get_current_state() const
{
	return __state;
}