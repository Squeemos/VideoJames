#include "TextureManager.h"
#include "Mesh.h"
#include "Error.h"
#include "Trace.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

#include <iostream>

static TextureManager tm = TextureManager();

TextureManager::TextureManager()
{
	std::cout << "Creating Texture Manager" << std::endl;
	stbi_set_flip_vertically_on_load(true);
}

TextureManager::~TextureManager()
{
	std::cout << "Destroying Texture Manager" << std::endl;
	textures.clear();
}

GLuint TextureManager::load_texture(const std::string& path, const std::string& dir, bool gamma)
{
	gamma;

	std::string filename = dir + '/' + path;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		else
		{
			format = GL_RED;
			send_trace_message("Texture may not be loaded correctly:" + filename);
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		send_trace_message("Texture failed to load at path: " + path);
		stbi_image_free(data);
	}

	return textureID;
}

std::shared_ptr<Texture> TextureManager::find(const std::string& path)
{
	const auto iterator = textures.find(path);
	if (iterator != textures.end())
		return iterator->second;
	else
		return nullptr;
}

void TextureManager::insert(std::shared_ptr<Texture> t)
{
	textures[t->path] = t;
}

std::shared_ptr<Texture> construct_texture(const std::string& path, const std::string& dir, const std::string& type_name, bool gamma)
{
	std::shared_ptr<Texture> found = tm.find(path);
	if (found)
		return found;
	else
	{
		found = std::make_shared<Texture>(path, type_name, tm.load_texture(path, dir, gamma));
		tm.insert(found);
		return found;
	}
}
