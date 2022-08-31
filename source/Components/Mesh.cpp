#include "Mesh.h"
#include "Texture.h"

#include "../Trace.h"
#include "../Errors.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texture_coordinates;
};

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Mesh::Mesh(const std::string& mesh_path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(mesh_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw EngineError(ErrorType::Graphics, "Error creating mesh from: " + mesh_path);
	}
	if (scene->mNumMeshes != 1)
	{
		throw EngineError(ErrorType::Graphics, "More than one mesh detected: " + mesh_path);
	}
	std::vector<Vertex> vs;
	std::vector<GLuint> is;

	aiMesh* mesh = scene->mMeshes[0];
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vert;
		vert.position.x = mesh->mVertices[i].x;
		vert.position.y = mesh->mVertices[i].y;
		vert.position.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vert.texture_coordinates.x = mesh->mTextureCoords[0][i].x;
			vert.texture_coordinates.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vert.texture_coordinates.x = 0.0f;
			vert.texture_coordinates.y = 0.0f;
		}

		vs.push_back(vert);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			is.push_back(face.mIndices[j]);
		}
	}

	num_indices = static_cast<GLsizei>(is.size());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vs.size() * sizeof(Vertex), vs.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, is.size() * sizeof(GLuint), is.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture_coordinates)));

	glBindVertexArray(0);
}

void Mesh::bind() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

void Mesh::unbind() const
{
	glBindVertexArray(0);
}
