#pragma once

#include <memory>
#include <string>

typedef unsigned int GLuint;
typedef int GLsizei;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void bind() const;
	void unbind() const;

private:
	GLuint VAO, VBO, EBO;
	GLsizei num_indices;
};
