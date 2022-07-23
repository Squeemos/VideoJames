#include "TextureManager.h"
#include "Texture.h"

#include <iostream>

static TextureManager tm = TextureManager();

TextureManager::TextureManager()
{
	std::cout << "Creating Texture Manager" << std::endl;

	// Reserve space for 10 textures, can be changed later
	textures.reserve(10 * sizeof(std::shared_ptr<Texture>));
}

TextureManager::~TextureManager()
{
	std::cout << "Destryoing Texture Manager" << std::endl;
	textures.clear();
}

std::shared_ptr<Texture> TextureManager::construct(const std::string& path, rgb_mode mode)
{
	// Try and find the texture
	for (auto& texture : textures)
	{
		if (texture->path == path && texture->mode == mode)
			return texture;
	}

	// Doesn't exist, so construct a new one
	std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(path, mode);
	textures.push_back(new_texture);

	return new_texture;
}

std::shared_ptr<Texture> construct_texture(const std::string& path, rgb_mode mode)
{
	return tm.construct(path, mode);
}
