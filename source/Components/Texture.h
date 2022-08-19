#pragma once

#include <string>

typedef unsigned int GLuint;

class Texture
{
public:
	Texture() = delete;
	Texture(const std::string& p);
	Texture(const std::string& p, const std::string& n);
	~Texture();

	void load_texture(const std::string& p);

	void bind() const;
	void unbind() const;

	GLuint id;
private:
	std::string path, name;
};

