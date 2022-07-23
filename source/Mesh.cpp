#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shader.h"
#include "Error.h"

#include <iostream>

Mesh::Mesh()
{
	throw MeshError();
}

Mesh::Mesh(GLfloat* v, GLuint n_v, GLuint* i, GLuint n_i, const std::string& n) : n_vertices(n_v), n_indices(n_i), name(n)
{
	std::cout << "Creating Mesh: " << name << std::endl;

	// Generate our vertex array and vertex buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind vertex array
	glBindVertexArray(VAO);

	// Bind the vertex buffer in static draw and fill the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, n_v * sizeof(GLfloat), v, GL_STATIC_DRAW);

	// Bind the ebo in static draw and fill the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_i * sizeof(GLuint), i, GL_STATIC_DRAW);

	// Tell the VAO what attributes to use

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Unbind the VBO -> safe to do
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// cannot unbind the EBO while the VAO is active since the stuff is bound in there
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <- no do

	// Unbind the VAO so we don't modify
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	std::cout << "Destroying Mesh: " << name << std::endl;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Mesh::bind_vao()
{
	// Draw vertices
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::unbind_vao()
{
	// Unbind the VAO
	glBindVertexArray(0);
}