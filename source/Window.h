#pragma once
#include <memory>

class Shader;
class Camera;
class Scene;

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
	void draw(Scene& scene);
	double get_dt();
	void frambuffer_size_callback(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	double previous_time, current_time;
	bool fullscreen;
	GLfloat red, green, blue;
	unsigned width, height;
	std::unique_ptr<Shader> shader_program;
};