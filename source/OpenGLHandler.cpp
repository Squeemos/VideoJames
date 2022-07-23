#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLHandler.h"
#include "Error.h"

#include <iostream>

OpenGLHandler::OpenGLHandler()
{
	std::cout << "Creating OpenGLHandler" << std::endl;

	// Init glfw
	if (!glfwInit())
		throw GLFWError();
}

OpenGLHandler::~OpenGLHandler()
{
	std::cout << "Destroying OpenGLHandler" << std::endl;

	// Terminate opengl
	glfwTerminate();
}