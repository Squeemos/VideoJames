#pragma once

#include <string>
#include <vector>
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model
{
public:
	Model();
	Model(const std::string& path);
	~Model();

	void draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void load_model(const std::string& path);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& type_name);
};

