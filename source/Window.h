#pragma once
#include <memory>

#include <glm/glm.hpp>

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
	glm::vec2& get_mouse();
	void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
	void frambuffer_size_callback(GLFWwindow* glfw_window, int window_width, int window_height);
	void mouse_callback(GLFWwindow* glfw_window, double x_pos, double y_pos);
	void reset();
	void swap_buffer();
private:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	double previous_time, current_time;
	bool fullscreen;
	GLfloat red, green, blue;
	unsigned width, height;
	glm::vec2 mouse;

};