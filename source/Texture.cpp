#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <sstream>
#include <iostream>

Texture::Texture()
{
	// Properly throw error at some point
	std::stringstream error;
	error << "Cannot use default ctor for Texture class..." << std::endl;
	std::cout << error.str();
	exit(EXIT_FAILURE);
}

Texture::Texture(const std::string& name, rgb_mode mode)
{
	std::cout << "Loading texture: " << name << std::endl;

	// Load a texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Have the texture's on the y-axis
	stbi_set_flip_vertically_on_load(true);

	GLint width, height, n_channels;
	stbi_uc* data = stbi_load(name.c_str(), &width, &height, &n_channels, 0);
	if (data)
	{
		// Load the texture based on which mode it is
		switch (mode)
		{
		case rgb_mode::rgb:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case rgb_mode::rgba:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			// Properly throw error at some point
			std::stringstream error;
			error << "Must use either rgb or rgba mode" << std::endl;
			std::cout << error.str();
			exit(EXIT_FAILURE);
			break;
		}

		// Generate the mipmap
		glGenerateMipmap(GL_TEXTURE_2D);

		// Free the image data since it's loaded on the GPU
		stbi_image_free(data);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		// Properly throw error at some point
		std::stringstream error;
		error << "Failed to load texture" << std::endl;
		std::cout << error.str();
		exit(EXIT_FAILURE);
	}
}

Texture::~Texture()
{
	std::cout << "Destryoing Texture" << std::endl;
}
