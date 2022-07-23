#pragma once

#include <string>

#include <glm/glm.hpp>

typedef unsigned int GLuint;
typedef float GLfloat;

class Mesh
{
public:
	Mesh();
	Mesh(GLfloat* v, GLuint n_v, GLuint* i, GLuint n_i, const std::string& n);
	~Mesh();
	void bind_vao();
	void unbind_vao();

	friend class MeshManager;

private:
	GLuint VBO, EBO, VAO, n_vertices, n_indices;
	std::string name;
};
