#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>

// Forward References
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void update();
void draw();

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
GLFWwindow* window;
GLFWmonitor* monitor;
bool fullscreen;

GLuint vertex_buffer, vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;

// Main
int main()
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


	// Set current context and load opengl with glad
	glfwMakeContextCurrent(window);
	gladLoadGL();

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

	// "Game" loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		draw();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void update()
{
}

void draw()
{
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

	glfwSwapBuffers(window);
}


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