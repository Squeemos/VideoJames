#include "NewShader.h"
#include "Error.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma warning(disable : 4201)
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

static std::string read_shader(std::string file_name);
static void check_shader(GLuint shader, const std::string& type);

NewShader::NewShader() : program_id(0)
{
}

NewShader::NewShader(const std::string& vertex_path, const std::string& fragment_path)
{
    GLuint vertex, fragment;
	std::string code;
	const GLchar* src;

	code = read_shader(vertex_path);
	src = code.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &src, NULL);
    glCompileShader(vertex);
    check_shader(vertex, "vertex");

    code = read_shader(fragment_path);
    src = code.c_str();
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &src, NULL);
    glCompileShader(fragment);
    check_shader(fragment, "fragment");

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex);
    glAttachShader(program_id, fragment);

    glLinkProgram(program_id);
    check_shader(program_id, "program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

NewShader::~NewShader()
{
}

void NewShader::use()
{
    glUseProgram(program_id);
}

void NewShader::unbind()
{
    glUseProgram(0);
}

void NewShader::set_int(const std::string& name, int value) const
{
	name;
	value;
}

void NewShader::set_mat4(const std::string& name, const glm::mat4& mat) const
{
    name;
    mat;
}

static std::string read_shader(std::string file_name)
{
	std::cout << "Loading shader: " << file_name << std::endl;

	std::string contents;
	std::ifstream file(file_name.c_str());
	if (!file.is_open())
	{
		throw ShaderError(std::string("File failed to open: " + file_name));
	}
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

static void check_shader(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw ShaderError("Error creating shader: " + type);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw ShaderError("Error creating shader program");
        }
    }
}