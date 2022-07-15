#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

class Shader;

typedef unsigned int GLuint;
typedef float GLfloat;

class Mesh
{
public:
	Mesh();
	Mesh(GLfloat* v, GLuint n_v, GLuint* i, GLuint n_i);
	~Mesh();
	void use_shader_program();
	void set_texture();
	void draw();
	void unbind();

	void shader_set_bool(const std::string& name, bool value) const;
	void shader_set_int(const std::string& name, int value) const;
	void shader_set_float(const std::string& name, float value) const;
	void shader_set_color(const std::string& name, glm::vec4 color) const;
	void shader_set_location(const std::string& name, glm::vec3 pos) const;
	void shader_set_mat4(const std::string& name, glm::mat4 mat) const;

private:
	std::shared_ptr<Shader> shader_program;
	GLuint VBO, EBO, VAO, n_vertices, n_indices;
};
