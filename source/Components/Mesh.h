#pragma once

#include <memory>
#include <string>

// Typedefs so we don't have to include glad/glfw
typedef unsigned int GLuint;
typedef int GLsizei;

// Class for a mesh that we will use to draw
class Mesh
{
public:
	// Constructor to build a mesh
	Mesh(const std::string& mesh_path);
	~Mesh();

	// Bind the VAO so it will actually draw
	void bind() const;
	void unbind() const;

private:
	// VAO : Vertex Array Object that holds all the relevant vertex data
	// VBO : Vertex Buffer Object that holds the vertex data
	// EBO : Element Buffer Object that holds the vertex index data
	GLuint VAO, VBO, EBO;

	// Number of indices for when we go to draw later since we need that info
	GLsizei num_indices;
};
