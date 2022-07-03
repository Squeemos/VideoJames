#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "Window.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>

// Forward References
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void update(double dt);
static void draw();
static std::string read_shader(std::string file_name);

// Constants
constexpr unsigned width{ 1280 };
constexpr unsigned height{ 720 };

// Static variables
static GLFWwindow* window;
static GLFWmonitor* monitor;
static bool fullscreen;
static double previous_time;
static GLfloat red, green, blue;
static GLuint vertex_shader, frag_shader, shader_program;
static GLuint VBO, VAO;

// Static temp variables to discard (only used for testing)
static float vertices[]{
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

// Initialize everything for the window
void window_init()
{
	// Set some window stuff (quality, resizable)
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA
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

	// Setting background colors
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;

	// Creating the vertex shader
	const GLchar* shader_src;
	std::string temp = read_shader("./shaders/vertex_shader.vert");
	shader_src = temp.c_str();
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &shader_src, NULL);
	glCompileShader(vertex_shader);

	// Check that the vertex shader properly compiled
	GLint success;
	GLchar info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "Vertex shader ran into a problem compiling" << std::endl << info_log << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Create the fragment shader
	temp = read_shader("./shaders/frag_shader.frag");
	shader_src = temp.c_str();
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &shader_src, NULL);
	glCompileShader(frag_shader);

	// Check that the fragment shader is properly compiled
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
		std::cout << "Fragment shader ran into a problem compiling" << std::endl << info_log << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Create the shader program
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, frag_shader);
	glLinkProgram(shader_program);

	// Check that the shader program was properly created
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "Linking the shaders into a program ran into a problem" << std::endl << info_log << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Delete the vertex and fragment shader since we no longer need them
	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

	// Create vertex array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate a vertex buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer

	// Copy vertices into buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy the vertices into the buffer. Static draw since this triangle won't move positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Set the attributes  for the buffer
	glEnableVertexAttribArray(0); // Enable the attributes
}

// Update the window
void window_update(double dt)
{
	// Check for input
	glfwPollEvents();

	// Update everything
	update(dt);

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
void update(double dt)
{
}

// Draw everything in the window
void draw()
{
	// Setup the buffer
	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw something
	glUseProgram(shader_program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the buffers to actually draw what we just loaded into them
	glfwSwapBuffers(window);
}

double get_dt()
{
	double current_time = glfwGetTime();
	double dt = current_time - previous_time;
	previous_time = current_time;
	return dt;
}

// Handles a small amount of inputs
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Exit the game
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// Make fullscreen or take from fullscreen to windowed
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		// Get the video mode of the monitor
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		
		// Set the window to be fullscreen (currently uses monitor's resolution and refresh rate, can later be adjusted)
		if (!fullscreen)
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		// Set the window to be windowed (currently uses const resolution and monitor refresh rate, can later be adjusted)
		else
			glfwSetWindowMonitor(window, NULL, 0, 0, width, height, mode->refreshRate);

		fullscreen = !fullscreen;
	}

	// Change the color of the background
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (red < 1.0f)
			red += .01f;
		if (blue < 1.0f)
			blue += .01f;
		if (green < 1.0f)
			green += .01f;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (red > 0.0f)
			red -= .01f;
		if (blue > 0.0f)
			blue -= .01f;
		if (green > 0.0f)
			green -= .01f;
	}
}

static std::string read_shader(std::string file_name)
{
	std::string contents;
	std::ifstream file(file_name.c_str());
	if (!file.is_open())
	{
		std::cout << "File failed to open: " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Loading shader: " << file_name << std::endl;
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}