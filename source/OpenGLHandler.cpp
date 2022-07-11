#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLHandler.h"

#include <iostream>

OpenGLHandler::OpenGLHandler()
{
	std::cout << "Creating OpenGLHandler" << std::endl;

	// Init glfw
	if (!glfwInit())
	{
		std::cout << "GLFW did not properly init..." << std::endl;
		exit(EXIT_FAILURE);
	}
}

OpenGLHandler::~OpenGLHandler()
{
	std::cout << "Destroying OpenGLHandler" << std::endl;

	// Terminate opengl
	glfwTerminate();
}