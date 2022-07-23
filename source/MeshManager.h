#pragma once

#include <vector>
#include <memory>

#include "Mesh.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	std::shared_ptr<Mesh> construct(const std::string& name);
private:
	std::vector<std::shared_ptr<Mesh>> meshes;
};

std::shared_ptr<Mesh> construct_mesh(const std::string& name);
