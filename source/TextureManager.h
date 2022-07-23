#pragma once

#include <vector>
#include <memory>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	std::shared_ptr<Texture> construct(const std::string& path, rgb_mode mode);
private:
	std::vector<std::shared_ptr<Texture>> textures;
};

std::shared_ptr<Texture> construct_texture(const std::string& path, rgb_mode mode);
