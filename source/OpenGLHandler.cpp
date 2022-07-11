#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLHandler.h"

#include <iostream>

OpenGLHandler::OpenGLHandler()
{
	// Init glfw
	if (!glfwInit())
	{
		std::cout << "GLFW did not properly init..." << std::endl;
		exit(EXIT_FAILURE);
	}
}

OpenGLHandler::~OpenGLHandler()
{
	glfwTerminate(); // Removed since added to openglhandler
	std::cerr << "Destroying" << std::endl;
}