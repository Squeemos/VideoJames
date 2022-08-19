#include "Texture.h"

#include "../Trace.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../External/stb_image.h"

Texture::Texture(const std::string& p) : path(p), name(p)
{
	stbi_set_flip_vertically_on_load(true);
	trace_message("Creating texture from: " + path);
	load_texture(p);
}

Texture::Texture(const std::string& p, const std::string& n) : path(p), name(n)
{
	stbi_set_flip_vertically_on_load(true);
	trace_message("Creating texture from: " + path + " with name: " + name);
	load_texture(p);
}

Texture::~Texture()
{
}

void Texture::load_texture(const std::string& p)
{
	glGenTextures(1, &id);

	int width, height, num_channels;
	unsigned char* data = stbi_load(p.c_str(), &width, &height, &num_channels, 0);
	if (data)
	{
		GLenum format;
		switch (num_channels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			std::abort();
			break;
		}

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}
