#pragma once

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
	void draw(double dt);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	double previous_time;
	bool fullscreen;
	GLfloat red, green, blue;
	unsigned width, height;
};

int check_key(int key);