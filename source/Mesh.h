#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

typedef unsigned int GLuint;
typedef float GLfloat;

class Mesh
{
public:
	Mesh();
	Mesh(GLfloat* v, GLuint n_v, GLuint* i, GLuint n_i);
	~Mesh();
	void bind_vao();
	void unbind_vao();

private:
	GLuint VBO, EBO, VAO, n_vertices, n_indices;
};
