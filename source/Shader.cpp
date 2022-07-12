#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

static std::string read_shader(std::string file_name);

Shader::Shader()
{
	// Properly throw error at some point
	std::stringstream error;
	error << "Cannot use default ctor for Shader class..." << std::endl;
	std::cout << error.str();
	exit(EXIT_FAILURE);
}

Shader::Shader(const std::string& path1, const std::string& path2)
{
	std::cout << "Creating Shader" << std::endl;

	// For error checking
	GLint success;
	GLchar info_log[1024];

	// For loading shaders
	std::string temp;
	const GLchar* shader_src;

	// Load the vertex shader
	temp = read_shader(path1);
	shader_src = temp.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &shader_src, NULL);
	glCompileShader(vertex_shader);
	
	// Check that the vertex shader is properly compiled
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 1024, NULL, info_log);

		// Properly throw error at some point
		std::stringstream error;
		error << "Vertex shader ran into a problem compiling" << std::endl << info_log << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}

	// Load the fragment shader
	temp = read_shader(path2);
	shader_src = temp.c_str();
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &shader_src, NULL);
	glCompileShader(frag_shader);

	// Check that the fragment shader is properly compiled
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Properly throw error at some point
		glGetShaderInfoLog(frag_shader, 1024, NULL, info_log);

		std::stringstream error;
		error << "Fragment shader ran into a problem compiling" << std::endl << info_log << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}

	// Create the shader program
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, frag_shader);
	glLinkProgram(program_id);

	// Check that the shader program was properly created
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		// Properly throw error at some point
		glGetProgramInfoLog(program_id, 512, NULL, info_log);

		std::stringstream error;
		error << "Linking the shaders into a program ran into a problem" << std::endl << info_log << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

Shader::~Shader()
{
	std::cout << "Destroying Shader" << std::endl;
}

void Shader::use()
{
	glUseProgram(program_id);
}

void Shader::set_bool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), static_cast<int>(value));
}

void Shader::set_int(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::set_color(const std::string& name, glm::vec4 color) const
{
	glUniform4f(glGetUniformLocation(program_id, name.c_str()), color.x, color.y, color.z, color.w);
}

void Shader::set_location(const std::string& name, glm::vec3 pos) const
{
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), pos.x, pos.y, pos.z);
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
