#pragma once

#include <string>
#include <vector>

#include "Trace.h" // Move to cpp along with the struct/class info

#include <glm/glm.hpp>

class Shader;
typedef unsigned int GLuint;
typedef float GLfloat;

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
	~Texture() { send_trace_message("Destroying Texture: " + path); }
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::vector<Texture> t);
	// Mesh(const GLfloat* v, GLuint n_v, const GLuint* i, GLuint n_i, const std::string& n);
	~Mesh();

	void draw(Shader& shader);

	friend class MeshManager;

protected:
	GLuint VBO, EBO, VAO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	void setup();
};
