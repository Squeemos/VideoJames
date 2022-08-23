#pragma once

#include "../Components/Mesh.h"

#include <unordered_map>
#include <string>

class MeshManager
{
public:
	MeshManager() {}
	~MeshManager() {}

	std::shared_ptr<Mesh> find_or_construct(std::string& mesh_name)
	{
		auto iterator = meshes.find(mesh_name);
		if (iterator != meshes.end())
			return iterator->second;
		else
		{
			std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>();
			meshes.insert(std::make_pair(mesh_name, new_mesh));

			return new_mesh;
		}
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
};

inline std::shared_ptr<Mesh> get_mesh(std::string mesh_name)
{
	static MeshManager mm = MeshManager();
	return mm.find_or_construct(mesh_name);
}