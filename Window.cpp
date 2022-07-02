#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "Window.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>

// Forward References
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_init();
static void update();
static void draw();

// Figure out what this does
// It's more variables but iduno
static const struct
{
	float x, y;
	float r, g, b;
} vertices[3] =
{
	{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
	{  0.6f, -0.4f, 0.f, 1.f, 0.f },
	{   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

// Constants
constexpr unsigned width = 1280;
constexpr unsigned height = 720;

// Static variables (make them actually static)
static GLFWwindow* window;
static GLFWmonitor* monitor;
static bool fullscreen;

static GLuint vertex_buffer, vertex_shader, fragment_shader, program;
static GLint mvp_location, vpos_location, vcol_location;

// Initialize everything for the window
void window_init()
{
	// Set some window stuff (quality, resizable)
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Init glfw
	if (!glfwInit())
	{
		std::cout << "GLFW did not properly init..." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Actually make the window
	window = glfwCreateWindow(width, height, "Title", NULL, NULL);
	if (!window)
	{
		std::cout << "Window failed to create..." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Input handler
	glfwSetKeyCallback(window, key_callback);

	// Set current context
	glfwMakeContextCurrent(window);

	// Load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set the monitor to the primary one
	monitor = glfwGetPrimaryMonitor();

	// Fullscreen is false
	fullscreen = false;

	// Something is happening here and I have no idea
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertices[0]), (void*)(sizeof(float) * 2));
}

// Update the window
void window_update()
{
	// Check for input
	glfwPollEvents();

	// Update everything
	update();

	// Draw everything
	draw();
}

// Shutdown the window
void window_shutdown()
{
	// Once done, cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Check to see if the window is still open
bool window_is_running()
{
	return !glfwWindowShouldClose(window);
}

// Window update
void update()
{
}

// Draw everything in the window
void draw()
{
	// Setup the buffer
	glViewport(0, 0, width, height);
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw something
	float ratio;
	int width, height;
	mat4x4 m, p, mvp;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	mat4x4_identity(m);
	mat4x4_rotate_Z(m, m, (float)glfwGetTime());
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);

	glUseProgram(program);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the buffers to actually draw what we just loaded into them
	glfwSwapBuffers(window);
}

// Handles a small amount of inputs (making fullscreen or closing the window)
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (!fullscreen)
			glfwSetWindowMonitor(window, monitor, 0, 0, width, height, 0);
		if (fullscreen)
			glfwSetWindowMonitor(window, NULL, 0, 0, width, height, 0);

		fullscreen = !fullscreen;
	}
}