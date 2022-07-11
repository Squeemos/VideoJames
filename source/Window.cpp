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
static void key_callback_function(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback_function(GLFWwindow* window, int width, int height);

// Static variables
static std::map<int, int> input_handler;

static GLuint vertex_shader, frag_shader, shader_program;
static GLuint VBO, EBO, VAO;

static GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

static unsigned int indices[] = { 0,1,3,1,2,3 };

// Initialize everything for the window
Window::Window() : fullscreen(false), red(0.0f), green(0.0f), blue(0.0f), width(640), height(640)
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

	// Setup for dt
	previous_time = glfwGetTime();
	current_time = glfwGetTime();

	// Set current context
	glfwMakeContextCurrent(window);

	// Update the user prointer of the window to this
	glfwSetWindowUserPointer(window, this);

	// Set the key callback function
	glfwSetKeyCallback(window, key_callback_function);

	// Set the resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_function);

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

	// Generate our vertex array and vertex buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind vertex array
	glBindVertexArray(VAO);

	// Bind the vertex buffer in static draw and fill the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the ebo in static draw and fill the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tell the VAO what attributes to use
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO -> safe to do
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// cannot unbind the EBO while the VAO is active since the stuff is bound in there
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <- no do

	// Unbind the VAO so we don't modify
	glBindVertexArray(0);
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
	// Update dt
	previous_time = current_time;

	// clear input buffer
	input_handler.clear();

	// Check for input
	glfwPollEvents();

	// Exit the game
	if (check_key(GLFW_KEY_ESCAPE))
	{
		// Set the window to close
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		// Return since there's nothing we should try and draw
		return;
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

	// Setup the buffer
	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw
	glUseProgram(shader_program);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Swap the buffers to actually draw what we just loaded into them
	glfwSwapBuffers(window);

	// Unbind the VAO
	glBindVertexArray(0);

	// Update dt
	current_time = glfwGetTime();
}

// Check to see if the window is still open
bool Window::running()
{
	return !glfwWindowShouldClose(window);
}

double Window::get_dt()
{
	return current_time - previous_time;
}

// Handles a small amount of inputs
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input_handler[key] = action;
}

void Window::frambuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// set the new height and width of the window
	glViewport(0, 0, width, height);
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
static void key_callback_function(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
}

static void framebuffer_size_callback_function(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->frambuffer_size_callback(window, width, height);
}