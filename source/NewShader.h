#pragma once

#include <string>
#include <glm/glm.hpp>

typedef unsigned int GLuint;

class NewShader
{
public:
	NewShader();
	NewShader(const std::string& vertex_path, const std::string& fragment_path);
	~NewShader();

	void use();
	void unbind();

	void set_int(const std::string& name, int value) const;
	void set_mat4(const std::string& name, const glm::mat4& mat) const;
private:
	GLuint program_id;
};