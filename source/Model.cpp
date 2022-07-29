#include "Model.h"
#include "Mesh.h"
#include "Error.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

static unsigned int texture_from_file(const std::string& path, const std::string& dir, bool gamma = false);

Model::Model()
{
}

Model::Model(const std::string& path)
{
	std::cout << "Creating Model: " << path << std::endl;
	stbi_set_flip_vertically_on_load(true);
	load_model(path);
}

Model::~Model()
{
}

void Model::draw(Shader& shader)
{
	for (auto& mesh : meshes)
		mesh.draw(shader);
}

void Model::load_model(const std::string& path)
{
	Assimp::Importer imp;
	const aiScene* scene = imp.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw ModelError("Error creating model from: " + path);
	}

	directory = path.substr(0, path.find_last_of('/'));

	process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		meshes.push_back(process_mesh(scene->mMeshes[node->mMeshes[i]], scene));

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		process_node(node->mChildren[i], scene);
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex v;
		v.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		v.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertices.push_back(v);

		if (mesh->mTextureCoords[0])
		{
			v.tex_coords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			v.tex_coords = glm::vec2(0.0f, 0.0f);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		std::vector<Texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");

		textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
		textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	}


	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& type_name)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString st;
		mat->GetTexture(type, i, &st);
		Texture texture;
		texture.id = texture_from_file(st.C_Str(), directory);
		texture.type = type_name;
		texture.path = std::string(st.C_Str());
		textures.push_back(texture);
	}
	return textures;
}

unsigned int texture_from_file(const std::string& path, const std::string& dir, bool gamma)
{
	gamma;

	std::string filename = dir + '/' + path;
	std::cout << "Creating texture from: " << filename << std::endl;

	GLuint texture_id;

	glGenTextures(1, &texture_id);

	int width, height, num_components;
	stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &num_components, 0);

	if (data)
	{
		GLenum format;
		if (num_components == 1)
			format = GL_RED;
		else if (num_components == 3)
			format = GL_RGB;
		else if (num_components == 4)
			format = GL_RGBA;
		else
		{
			stbi_image_free(data);
			throw TextureError("Format of image not implemented, from file: " + filename);
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// handle for tiling or not
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		throw TextureError("Error creating texture from: " + filename);
	}

	return texture_id;
}
