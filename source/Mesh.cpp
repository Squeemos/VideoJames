#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Error.h"
#include "Shader.h"
#include "Trace.h"

#include <iostream>

Mesh::Mesh()
{
	throw MeshError("Trying to create default mesh");
}

Mesh::Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::vector<Texture> t) : vertices(v), indices(i), textures(t), VAO(0), VBO(0), EBO(0)
{
	send_trace_message("Creating Mesh");
	setup();
}

//Mesh::Mesh(const GLfloat* v, GLuint n_v, const GLuint* i, GLuint n_i, const std::string& n) : n_vertices(n_v), n_indices(n_i), name(n)
//{
//	std::cout << "Creating Mesh: " << name << std::endl;
//
//	// Generate our vertex array and vertex buffers
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	// Bind vertex array
//	glBindVertexArray(VAO);
//
//	// Bind the vertex buffer in static draw and fill the buffer
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, n_v * sizeof(GLfloat), v, GL_STATIC_DRAW);
//
//	// Bind the ebo in static draw and fill the buffer
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_i * sizeof(GLuint), i, GL_STATIC_DRAW);
//
//	// Tell the VAO what attributes to use
//
//	// Position
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// Color
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	// Texture Coordinates
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	// Unbind the VBO -> safe to do
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// cannot unbind the EBO while the VAO is active since the stuff is bound in there
//	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <- no do
//
//	// Unbind the VAO so we don't modify
//	glBindVertexArray(0);
//}

Mesh::~Mesh()
{
	send_trace_message("Destroying Mesh");
	
	// Delete the vao and the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::setup()
{
	assert(vertices.size());
	assert(indices.size());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

	glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
	GLuint diffuse = 1;
	GLuint specular = 1;

	for (auto i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string tex_num;
		std::string tex_name = textures[i].type;

		if (tex_name == "texture_diffuse")
			tex_num = std::to_string(diffuse++);
		else if (tex_name == "texture_specular")
			tex_num = std::to_string(specular++);
		else
			throw std::runtime_error("Trying to set uniform that doesn't exist");

		shader.set_int(("material" + tex_name + tex_num).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}


//void Mesh::bind_vao()
//{
//	// Draw vertices
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//}
//
//void Mesh::unbind_vao()
//{
//	// Unbind the VAO
//	glBindVertexArray(0);
//}