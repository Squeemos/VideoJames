#include "Shader.h"
#include "Error.h"
#include "Trace.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma warning(disable : 4201)
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

static std::string read_shader(std::string file_name);

Shader::Shader() : program_id(0), vert_path(""), frag_path("")
{
	throw ShaderError("Creating blank shader");
}

Shader::Shader(const std::string& vertex, const std::string& fragment) : vert_path(vertex), frag_path(fragment)
{
	// For error checking
	GLint success;
	GLchar info_log[1024];

	// For loading shaders
	std::string temp;
	const GLchar* shader_src;

	// Load the vertex shader
	temp = read_shader(vertex);
	shader_src = temp.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &shader_src, NULL);
	glCompileShader(vertex_shader);
	
	// Check that the vertex shader is properly compiled
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 1024, NULL, info_log);

		std::stringstream error;
		error << "Vertex shader ran into a problem compiling" << std::endl << info_log << std::endl;
		throw ShaderError(error.str());
	}

	// Load the fragment shader
	temp = read_shader(fragment);
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

		// Delete vertex shader before exiting
		glDeleteShader(vertex_shader);

		throw ShaderError(error.str());
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
		// Get info of error
		glGetProgramInfoLog(program_id, 1024, NULL, info_log);

		// Delete the shaders before throwing
		glDeleteShader(vertex_shader);
		glDeleteShader(frag_shader);

		throw ProgramError("Linking the shaders into a program ran into a problem");
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

Shader::~Shader()
{
	send_trace_message("Destroying Shader " + vert_path + " " + frag_path);
}

void Shader::use()
{
	glUseProgram(program_id);
}

void Shader::unuse()
{
	glUseProgram(0);
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

void Shader::set_vec4(const std::string& name, glm::vec4 vec) const
{
	glUniform4f(glGetUniformLocation(program_id, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::set_mat4(const std::string& name, glm::mat4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, false, glm::value_ptr(mat));
}

void Shader::set_vec3(const std::string& name, glm::vec3 vec) const
{
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), vec.x, vec.y, vec.z);
}

static std::string read_shader(std::string file_name)
{
	send_trace_message("Loading shader: " + file_name);

	std::string contents;
	std::ifstream file(file_name.c_str());
	if (!file.is_open())
	{
		throw ShaderError("File failed to open: " + file_name);
	}

	std::string ret = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	return ret;
}
