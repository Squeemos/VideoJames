#pragma once
#include <exception>
#include <sstream>

// These errors are useful for specific cases if we need to do catch specific behavior for exiting
// For example, if we catch a shader error, we may need to free another error or something

// When GLFW fails to init
class GLFWError : public std::exception
{
public:
	const char* what() const { return "Failed to initialize GLFW"; }
};

// When window fails to be created
class WindowError : public std::exception
{
public:
	const char* what() const { return "Error creating window"; }
};

// When glad fails to init
class GladError : public std::exception
{
public:
	const char* what() const { return "Failed to initialize GLAD"; }
};

// When shader fails to be created
class ShaderError : public std::exception
{
public:
	ShaderError(const std::string& message) : message_(message) {}
	const char* what() const { return message_.c_str(); }
private:
	std::string message_;
};

// When opengl program fails to be created
class ProgramError : public std::exception
{
public:
	ProgramError(const std::string& message) : message_(message) {}
	const char* what() const { return message_.c_str(); }
private:
	std::string message_;
};

// When texture fails to be created
class TextureError : public std::exception
{
public:
	TextureError(const std::string& message) : message_(message) {}
	const char* what() const { return message_.c_str(); }
private:
	std::string message_;
};