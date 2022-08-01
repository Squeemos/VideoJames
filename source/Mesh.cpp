#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Error.h"
#include "Shader.h"

#include <iostream>

Mesh::Mesh()
{
	throw MeshError("Trying to create default mesh");
}

Mesh::Mesh(const std::vector<Vertex>& v, const std::vector<GLuint>& i, std::vector<std::shared_ptr<Texture>> t)
{
	send_trace_message("Creating Mesh");

	// Make sure the mesh we're creating has stuff in it, otherwise there's problems
	assert(v.size());
	assert(i.size());

	// Set the textures
	textures = t;

	// Set the number of indices since we'll need this for drawing
	num_indices = static_cast<GLsizei>(i.size());

	// Below is all OpenGL stuff, this will get edited as meshes become more complex
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(Vertex), v.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(GLuint), i.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

	glBindVertexArray(0);
}

// Move ctor
Mesh::Mesh(Mesh&& other) noexcept
{
	VBO = other.VBO;
	other.VBO = 0;

	EBO = other.EBO;
	other.EBO = 0;

	VAO = other.VAO;
	other.VAO = 0;

	num_indices = other.num_indices;
	other.num_indices = 0;

	textures = std::move(other.textures);
}

// Move assignment operator
Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	VBO = other.VBO;
	other.VBO = 0;

	EBO = other.EBO;
	other.EBO = 0;

	VAO = other.VAO;
	other.VAO = 0;

	num_indices = other.num_indices;
	other.num_indices = 0;

	textures = std::move(other.textures);

	return *this;
}

Mesh::~Mesh()
{
	send_trace_message("Destroying Mesh");
	
	// Delete the vao and the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::draw(Shader& shader)
{
	GLuint diffuse = 1;
	GLuint specular = 1;

	// If there's textures to draw
	if (textures.size() != 0)
	{
		shader.set_int("textured", 1);
		for (auto i = 0; i < textures.size(); ++i)
		{
			// Set the current texture pointer
			glActiveTexture(GL_TEXTURE0 + i);

			std::string tex_num;
			std::string tex_name = textures[i]->type;

			// Get the type of texture it is
			if (tex_name == "texture_diffuse")
				tex_num = std::to_string(diffuse++);
			else if (tex_name == "texture_specular")
				tex_num = std::to_string(specular++);
			else
				throw std::runtime_error("Trying to set uniform that doesn't exist");

			// Set the uniform
			shader.set_int(("material" + tex_name + tex_num).c_str(), i);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i]->id);
		}
	}
	// Otherwise draw the mesh with vertices
	else
	{
		shader.set_int("textured", 0);
		shader.set_vec4("other_color", glm::vec4(1.0f, 0.6f, 0.0f, 1.0f));
	}

	// Actual draw step
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}