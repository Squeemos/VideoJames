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

Mesh::Mesh(GLfloat* v, GLuint n_v, GLuint* i, GLuint n_i)
{
	std::cout << "Creating Mesh" << std::endl;

	// Create the shader program
	shader_program = std::make_unique<Shader>("./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");

	// Generate our vertex array and vertex buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind vertex array
	glBindVertexArray(VAO);

	// Bind the vertex buffer in static draw and fill the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, n_v, v, GL_STATIC_DRAW);

	// Bind the ebo in static draw and fill the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_i, i, GL_STATIC_DRAW);

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::use_shader_program()
{
	// Use the shader
	shader_program->use();
}

void Mesh::set_texture()
{
	// Set the texture
	shader_program->set_int("texture1", 0);
}

void Mesh::draw()
{
	// Draw vertices
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::unbind()
{
	// Unbind the VAO
	glBindVertexArray(0);
}

void Mesh::shader_set_bool(const std::string& name, bool value) const
{
	shader_program->set_bool(name, value);
}
void Mesh::shader_set_int(const std::string& name, int value) const
{
	shader_program->set_int(name, value);
}
void Mesh::shader_set_float(const std::string& name, float value) const
{
	shader_program->set_float(name, value);
}
void Mesh::shader_set_color(const std::string& name, glm::vec4 color) const
{
	shader_program->set_color(name, color);
}
void Mesh::shader_set_location(const std::string& name, glm::vec3 pos) const
{
	shader_program->set_location(name, pos);
}
void Mesh::shader_set_mat4(const std::string& name, glm::mat4 mat) const
{
	shader_program->set_mat4(name, mat);
}