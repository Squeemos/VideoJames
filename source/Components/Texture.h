#pragma once

#include <string>

// Typedef so we don't need to include glfw/glad
typedef unsigned int GLuint;

// A class for textures so we can add images to what we draw
class Texture
{
public:
	// No default texture since that doesn't make any sense
	Texture() = delete;

	// Non-default constructor that will build from the path
	// TODO : add in other options when loading so we use the texture for tiling or other things
	Texture(const std::string& p);
	~Texture();

	// Used to actually load the texture in case we need to do something else
	void load_texture(const std::string& p);

	// Binding so the texture will actually draw
	void bind() const;
	void unbind() const;

private:
	// Internal id for drawing
	GLuint id;
};

