#pragma once

#include <glm/glm.hpp>

#include <string>

// typedef so we don't have to include glfw/glad
typedef unsigned int GLuint;

// Shader class which is a wrapper around opengl shaders
class Shader
{
public:
	// No default constructor
	Shader() = delete;

	// Non-default constructors
	Shader(const std::string& vertex, const std::string& fragment);
	Shader(const std::string& vertex, const std::string& fragment, const std::string& n);
	~Shader();

	// Use the shader program to draw things
	void use();
	void unuse();

	// Interact with the different uniforms
	void set_uniform(const std::string& n, bool value) const;
	void set_uniform(const std::string& n, int value) const;
	void set_uniform(const std::string& n, float value) const;
	void set_uniform(const std::string& n, const glm::vec2 vec2) const;
	void set_uniform(const std::string& n, const glm::vec3 vec3) const;
	void set_uniform(const std::string& n, const glm::mat4 mat4) const;

private:
	// Program id is the opengl program id of the shader
	GLuint __program_id;

	// Vertex Path and Fragment Path are the paths to each part of the shader
	// The name is the name of the shader, and if none is ever given, it's the two paths concatenated
	std::string __vertex_path, __fragment_path, __name;

	// Method for loading in the shaders
	void load_shader(const std::string& vertex, const std::string& fragment);
};