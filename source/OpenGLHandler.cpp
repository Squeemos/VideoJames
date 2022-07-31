#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLHandler.h"
#include "Error.h"
#include "Trace.h"

#include <iostream>

OpenGLHandler::OpenGLHandler()
{
	send_trace_message("Creating OpenGLHandler");

	// Init glfw
	if (!glfwInit())
		throw GLFWError();
}

OpenGLHandler::~OpenGLHandler()
{
	send_trace_message("Destryoing OpenGLHandler");

	// Terminate opengl
	glfwTerminate();
}