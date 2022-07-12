#pragma once

#include <string>
#include "stb_image.h"

typedef unsigned int GLuint;

enum class rgb_mode
{
	rgb,
	rgba
};

class Texture
{
public:
	Texture();
	Texture(const std::string& name, rgb_mode mode);
	~Texture();

	GLuint texture;
};

