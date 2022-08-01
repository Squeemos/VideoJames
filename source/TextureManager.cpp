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
	//std::cout << "Creating Texture Manager" << std::endl;
	send_trace_message("Creating Texture Manager");
	stbi_set_flip_vertically_on_load(true);
}

TextureManager::~TextureManager()
{
	//std::cout << "Destroying Texture Manager" << std::endl;
	send_trace_message("Destroying Texture Manager");
	textures.clear();
}

GLuint TextureManager::load_texture(const std::string& path, const std::string& dir, bool gamma)
{
	gamma;

	// Get the path to the texture
	std::string filename = dir + '/' + path;

	// Generate a texture in opengl
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Read in the texture with stb_image
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

		// Use opengl to bind the texture to the id
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Maybe have something to determine if we're tiling or not
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
	// If we've already loaded the texture, just go get it
	const auto& iterator = textures.find(path);
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
	// Get the path to the texture
	std::string filename = dir + '/' + path;
	// See if it's already been loaded, if it has return it
	std::shared_ptr<Texture> found = tm.find(filename);
	if (found)
		return found;
	// Otherwise, load the texture and store it so we can make copies
	else
	{
		found = std::make_shared<Texture>(filename, type_name, tm.load_texture(path, dir, gamma));
		tm.insert(found);
		return found;
	}
}
