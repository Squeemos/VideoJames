#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "linmath.h"

#include "Window.h"
#include "Entity.h"
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <utility>
#include <map>
#include <sstream>
#include <string>

// Forward References
static void key_callback_function(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback_function(GLFWwindow* window, int width, int height);
// Static variables
static std::map<int, int> input_handler;

static GLuint VBO, EBO, VAO;

static std::unique_ptr<Texture> t1, t2;

static GLfloat vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

static GLuint indices[] = { 0,1,3,1,2,3 };

static GLfloat border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };

// Initialize everything for the window
Window::Window() : fullscreen(false), red(0.0f), green(0.0f), blue(0.0f), width(640), height(640)
{
	std::cout << "Creating Window" << std::endl;

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

	// Load the shaders class
	shader_program = std::make_unique<Shader>("./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");

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

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Unbind the VBO -> safe to do
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// cannot unbind the EBO while the VAO is active since the stuff is bound in there
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <- no do

	// Unbind the VAO so we don't modify
	glBindVertexArray(0);

	t1 = std::make_unique<Texture>("./assets/rgb_tex.jpg", rgb_mode::rgb);
	t2 = std::make_unique<Texture>("./assets/rgba_tex.png", rgb_mode::rgba);
}

// Shutdown the window
Window::~Window()
{
	std::cout << "Destroying Window" << std::endl;
	// Once done, cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
	shader_program->use();

	// Set the texture
	shader_program->set_int("texture1", 0);

	// Make it move around
	GLfloat time = glfwGetTime();
	GLfloat x = cos(time) / 2.0f;
	GLfloat y = sin(time) / 2.0f;
	shader_program->set_location("loc", glm::vec3(x, y, 0));

	// Draw textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t1->texture);

	// Draw vertices
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Set the texture
	shader_program->set_int("texture1", 0);

	// Make it move around
	x = -cos(time) / 2.0f;
	y = -sin(time) / 2.0f;
	shader_program->set_location("loc", glm::vec3(x, y, 0));

	// Draw textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t2->texture);

	// Draw vertices
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

void Window::frambuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// set the new height and width of the window
	glViewport(0, 0, width, height);
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
static void key_callback_function(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input_handler[key] = action;
}

static void framebuffer_size_callback_function(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->frambuffer_size_callback(window, width, height);
}