#pragma once
#include <memory>

class Shader;

typedef struct GLFWwindow GLFWwindow;
typedef struct GLFWmonitor GLFWmonitor;
typedef float GLfloat;

class Window
{
public:
	Window();
	~Window();
	bool running();
	void update(double dt);
	double get_dt();
	void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
	void frambuffer_size_callback(GLFWwindow* glfw_window, int window_width, int window_height);
	void reset();
	void swap_buffer();
private:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	double previous_time, current_time;
	bool fullscreen;
	GLfloat red, green, blue;
	unsigned width, height;
	std::unique_ptr<Shader> shader_program;
};