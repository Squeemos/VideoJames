#include "Texture.h"

#include "../Trace.h"
#include "../Errors.h"

#include <glad/glad.h>

#include "../External/stb_image.h"

Texture::Texture(const std::string& p, TextureType type)
{
	load_texture(p, type);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::load_texture(const std::string& p, TextureType type)
{
	trace_message("Creating texture from: " + p);
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
			throw EngineError(ErrorType::Graphics, "Invalid texture type from: " + p);
			break;
		}

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		switch (type)
		{
		case TextureType::Tile:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TextureType::MirroredTile:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		case TextureType::Single:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		default:
			trace_message("Invalid type provided for: " + p + " assuming single");
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	else
	{
		throw EngineError(ErrorType::Graphics, "Error creating texture from: " + p);
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
