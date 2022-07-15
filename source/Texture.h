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

	void use();

private:
	GLuint texture;
	Texture();
};

