#include "Graphics.h"
#include "../Errors.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma warning(disable : 4201)
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

static std::string read_shader(std::string file_name);

Shader::Shader(const std::string& vertex, const std::string& fragment) : __vertex_path(vertex), __fragment_path(fragment), __name(vertex + fragment)
{
	load_shader(vertex, fragment);
}

Shader::Shader(const std::string& vertex, const std::string& fragment, const std::string& n) : __vertex_path(vertex), __fragment_path(fragment), __name(n)
{
	load_shader(vertex, fragment);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(__program_id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::set_uniform(const std::string& n, bool value) const
{
	glUniform1i(glGetUniformLocation(__program_id, n.c_str()), static_cast<int>(value));
}

void Shader::set_uniform(const std::string& n, int value) const
{
	glUniform1i(glGetUniformLocation(__program_id, n.c_str()), static_cast<int>(value));
}

void Shader::set_uniform(const std::string& n, float value) const
{
	glUniform1f(glGetUniformLocation(__program_id, n.c_str()), value);
}

void Shader::set_uniform(const std::string& n, const glm::vec2 vec2) const
{
	glUniform2f(glGetUniformLocation(__program_id, n.c_str()), vec2.x, vec2.y);
}

void Shader::set_uniform(const std::string& n, const glm::vec3 vec3) const
{
	glUniform3f(glGetUniformLocation(__program_id, n.c_str()), vec3.x, vec3.y, vec3.z);
}

void Shader::set_uniform(const std::string& n, const glm::mat4 mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(__program_id, n.c_str()), 1, false, glm::value_ptr(mat4));
}

void Shader::load_shader(const std::string& vertex, const std::string& fragment)
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
		throw EngineError(ErrorType::Graphics, info_log);
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
		// Delete vertex shader before exiting
		glDeleteShader(vertex_shader);

		throw EngineError(ErrorType::Graphics, info_log);
	}

	// Create the shader program
	__program_id = glCreateProgram();
	glAttachShader(__program_id, vertex_shader);
	glAttachShader(__program_id, frag_shader);
	glLinkProgram(__program_id);

	// Check that the shader program was properly created
	glGetProgramiv(__program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		// Get info of error
		glGetProgramInfoLog(__program_id, 1024, NULL, info_log);

		// Delete the shaders before throwing
		glDeleteShader(vertex_shader);
		glDeleteShader(frag_shader);

		throw EngineError(ErrorType::Graphics, info_log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

static std::string read_shader(std::string file_name)
{
	std::string contents;
	std::ifstream file(file_name.c_str());
	if (!file.is_open())
	{
		throw EngineError(ErrorType::Graphics, "Unable to open file: " + file_name);
	}

	std::string ret = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	return ret;
}