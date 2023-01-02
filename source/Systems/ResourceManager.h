#pragma once

#include "../Components/Mesh.h"
#include "../Components/Texture.h"

#include "../External/stb_image.h"

#include <unordered_map>
#include <string>

// Class that manages all resources that need to be loaded
class ResourceManager
{
private:
	ResourceManager() = default;
	~ResourceManager() = default;

	// To prevent copying
	ResourceManager(ResourceManager&& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager&& other) = delete;

public:
	// Get the instance of the resource manager
	inline static ResourceManager& get_instance()
	{
		static ResourceManager rm;
		return rm;
	}

	inline std::shared_ptr<Mesh> find_or_construct_mesh(const std::string& mesh_name)
	{
		// See if we can find the mesh
		auto iterator = __meshes.find(mesh_name);
		if (iterator != __meshes.end())
			return iterator->second;
		else
		{
			// Create it if it doesn't exist
			std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>("./data/meshes/" + mesh_name + ".obj");
			//std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>();
			__meshes.insert(std::make_pair(mesh_name, new_mesh));

			return new_mesh;
		}
	}

	inline std::shared_ptr<Texture> find_or_construct_texture(const std::string& texture_name, TextureType type)
	{
		// See if we can find the texture
		auto iterator = __textures.find(texture_name);
		if (iterator != __textures.end())
			return iterator->second;
		else
		{
			// Create it if it doesn't exist
			std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(texture_name, type);
			__textures.insert(std::make_pair(texture_name, new_texture));

			return new_texture;
		}
	}

private:
	// Unordered maps of the resources we want to manage
	std::unordered_map<std::string, std::shared_ptr<Mesh>> __meshes;
	std::unordered_map<std::string, std::shared_ptr<Texture>> __textures;
};