#include "NewMesh.h"
#include "Error.h"
#include "NewShader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

NewMesh::NewMesh() : VAO(0), VBO(0), EBO(0)
{
	std::cout << "Creating NewMesh" << std::endl;
}

NewMesh::NewMesh(std::vector<NewVertex> verts, std::vector<GLuint> inds, std::vector<NewTexture> texts) : vertices(verts), indices(inds), textures(texts), VAO(0), VBO(0), EBO(0)
{
	std::cout << "Creating NewMesh" << std::endl;

	setup();
}

NewMesh::~NewMesh()
{
	std::cout << "Destroying NewMesh" << std::endl;
}

void NewMesh::draw(NewShader& shader)
{
	GLuint diffuse_num = 1, specular_num = 1, normal_num = 1, height_num = 1;

	for (auto i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);


		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuse_num++);
		else if (name == "texture_specular")
			number = std::to_string(specular_num++);
		else if (name == "texture_normal")
			number = std::to_string(normal_num++);
		else if (name == "texture_height")
			number = std::to_string(height_num++);

		shader.set_int(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLuint>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void NewMesh::setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(NewVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, tex_coords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, bitangent));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_INT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, bone_ids));

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(NewVertex), (void*)offsetof(NewVertex, weights));

	glBindVertexArray(0);
}
