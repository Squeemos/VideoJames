#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "Window.h"
#include "Entity.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <utility>
#include <map>
#include <sstream>
#include <string>

// Forward References
static std::string read_shader(std::string file_name);
void callback_function(GLFWwindow* window, int key, int scancode, int action, int mods);

// Static variables
static std::map<int, int> input_handler;

static GLuint vertex_shader, frag_shader, shader_program;
static GLuint VBO, VAO;

static Entity John = Entity();

// Initialize everything for the window
Window::Window() : fullscreen(false), red(0.0f), green(0.0f), blue(0.0f), width(1280), height(720)
{
	// Set some window stuff (quality, resizable)
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Actually make the window
	window = glfwCreateWindow(width, height, "Title", NULL, NULL);
	if (!window)
	{
		// Properly throw error at some point
		std::stringstream error;
		error << "Window failed to create..." << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}

	// Set the previous time
	previous_time = glfwGetTime();

	// Update the user prointer of the window to this
	glfwSetWindowUserPointer(window, this);

	// Set the key callback function
	glfwSetKeyCallback(window, callback_function);

	// Set current context
	glfwMakeContextCurrent(window);

	// Load glad -> has to be done after glfwinit and window init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Properly throw error at some point
		std::stringstream error;
		error << "Failed to initialize GLAD" << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}

	// Set the monitor to the primary one
	monitor = glfwGetPrimaryMonitor();

	// Set the buffer swap interval to 0 (no vsync)
	glfwSwapInterval(0);

	// Perhaps make a shader class of everything below ------------------------------------

	// Creating the vertex shader
	std::string temp = read_shader("./shaders/vertex_shader.vert");
	const GLchar* shader_src = temp.c_str();
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

		// Properly throw error at some point
		std::stringstream error;
		error << "Vertex shader ran into a problem compiling" << std::endl << info_log << std::endl;
		std::cout << error.str();
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
		// Properly throw error at some point
		glGetShaderInfoLog(frag_shader, 512, NULL, info_log);

		std::stringstream error;
		error << "Fragment shader ran into a problem compiling" << std::endl << info_log << std::endl;
		std::cout << error.str();
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
		// Properly throw error at some point
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);

		std::stringstream error;
		error << "Linking the shaders into a program ran into a problem" << std::endl << info_log << std::endl;
		std::cout << error.str();
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
}

// Shutdown the window
Window::~Window()
{
	std::cout << "Destroying Window" << std::endl;
	// Once done, cleanup
	glfwDestroyWindow(window);
}

// Update the window
void Window::update(double dt)
{
	// Check for input
	glfwPollEvents();

	// Exit the game
	if (check_key(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// Make fullscreen or take from fullscreen to windowed
	if (check_key(GLFW_KEY_F) == GLFW_PRESS)
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

	John.update(dt);
	std::pair<float*, unsigned long long> verts_and_num = John.draw();

	// Copy vertices into buffer
	glBufferData(GL_ARRAY_BUFFER, verts_and_num.second, verts_and_num.first, GL_DYNAMIC_DRAW); // Copy the vertices into the buffer. Static draw since this triangle won't move positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Set the attributes  for the buffer
	glEnableVertexAttribArray(0); // Enable the attributes

	// Draw everything
	draw(dt);
}

// Check to see if the window is still open
bool Window::running()
{
	return !glfwWindowShouldClose(window);
}

double Window::get_dt()
{
	double current_time = glfwGetTime();
	double dt = current_time - previous_time;
	previous_time = current_time;
	return dt;
}

// Draw everything in the window
void Window::draw(double dt)
{
	// Setup the buffer
	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw something
	glUseProgram(shader_program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Swap the buffers to actually draw what we just loaded into them
	glfwSwapBuffers(window);
}

// Handles a small amount of inputs
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input_handler[key] = action;
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

// Check if keys are pressed
int check_key(int key)
{
	const auto iterator = input_handler.find(key);
	if (iterator != input_handler.end())
		return iterator->second;
	else
		return 0;
}

// Input handler
// Maybe there's a better way to do this
// Make this a static function so it's not a lambda
void callback_function(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
}