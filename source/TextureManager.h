#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>

struct Texture;
typedef unsigned int GLuint;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	GLuint load_texture(const std::string& path, const std::string& dir, bool gamma);
	std::shared_ptr<Texture> find(const std::string& path);
	void insert(std::shared_ptr<Texture> t);
private:
	std::map<std::string, std::shared_ptr<Texture>> textures;
};

std::shared_ptr<Texture> construct_texture(const std::string& path, const std::string& dir, const std::string& type_name, bool gamma = false);