#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;
class NewShader;

struct NewVertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	GLint bone_ids[4];
	GLfloat weights[4];
};

struct NewTexture
{
public:
	GLuint id;
	std::string type, path;
};

class NewMesh
{
public:
	NewMesh();
	NewMesh(std::vector<NewVertex> verts, std::vector<GLuint> inds, std::vector<NewTexture> texts);
	~NewMesh();

	void draw(NewShader& shader);

	std::vector<NewVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<NewTexture> textures;

	GLuint VAO;

private:
	void setup();

	GLuint VBO, EBO;
};

