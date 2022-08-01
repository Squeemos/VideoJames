#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Trace.h" // Move to cpp along with the struct/class info

#include <glm/glm.hpp>

class Shader;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef int GLsizei;

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};

struct Texture
{
public:
	Texture(const std::string& p, const std::string& t, GLuint i) : path(p), type(t), id(i) { send_trace_message("Creating Texture: " + path); }
	~Texture() { send_trace_message("Destroying Texture: " + path); }
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<Vertex>& v, const std::vector<GLuint>& i, std::vector<std::shared_ptr<Texture>> t);
	Mesh(Mesh&& other) noexcept;
	// Mesh(const GLfloat* v, GLuint n_v, const GLuint* i, GLuint n_i, const std::string& n);
	~Mesh();

	Mesh& operator=(Mesh&& other) noexcept;

	void draw(Shader& shader);

protected:
	GLuint VBO, EBO, VAO;
	GLsizei num_indices;
	std::vector<std::shared_ptr<Texture>> textures;
};
