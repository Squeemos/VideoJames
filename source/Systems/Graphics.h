#pragma once

#include <glm/glm.hpp>

#include <string>

typedef unsigned int GLuint;

class Shader
{
public:
	Shader() = delete;
	Shader(const std::string& vertex, const std::string& fragment);
	Shader(const std::string& vertex, const std::string& fragment, const std::string& n);
	~Shader();

	void use();
	void unuse();

	void set_uniform(const std::string& n, bool value) const;
	void set_uniform(const std::string& n, int value) const;
	void set_uniform(const std::string& n, float value) const;
	void set_uniform(const std::string& n, const glm::vec2 vec2) const;
	void set_uniform(const std::string& n, const glm::vec3 vec3) const;
	void set_uniform(const std::string& n, const glm::mat4 mat4) const;

private:
	GLuint program_id;
	std::string vertex_path, fragment_path, name;

	void load_shader(const std::string& vertex, const std::string& fragment);
};