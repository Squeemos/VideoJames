#pragma once

#include <string>

typedef unsigned int GLuint;

enum class rgb_mode
{
	rgb,
	rgba
};

class Texture
{
public:
	Texture(const std::string& name, rgb_mode mode);
	~Texture();

	GLuint texture; // Make private at some point

private:
	Texture();
};

