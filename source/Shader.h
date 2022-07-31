#pragma once
#include <string>
#include <glm/glm.hpp>

typedef unsigned int GLuint;

class Shader
{
public:
	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();
	void use();

	void unbind();

	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	void set_mat4(const std::string& name, glm::mat4 mat) const;
	void set_vec4(const std::string& name, glm::vec4 vec) const;

	friend class ShaderManager;

private:
	GLuint program_id;
	std::string vert_path, frag_path;
};