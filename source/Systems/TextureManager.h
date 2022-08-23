#pragma once
#include "../Components/Texture.h"

#include <unordered_map>
#include <string>

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	std::shared_ptr<Texture> find_or_construct(std::string& texture_name)
	{
		auto iterator = textures.find(texture_name);
		if (iterator != textures.end())
			return iterator->second;
		else
		{
			std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(texture_name);
			textures.insert(std::make_pair(texture_name, new_texture));

			return new_texture;
		}
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
};

inline std::shared_ptr<Texture> get_texture(std::string texture_name)
{
	static TextureManager tm = TextureManager();
	return tm.find_or_construct(texture_name);
}