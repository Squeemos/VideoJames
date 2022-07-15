#pragma once
#include <utility>
#include <memory>
#include <string>
#include <glm/glm.hpp>

class Texture;
class Mesh;
enum class rgb_mode;

class Entity
{
public:
	Entity();
	Entity(glm::vec3 new_pos, const std::string& texture, rgb_mode mode, std::string name);
	~Entity();
	void draw();
	void update(double dt);

	float speed;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	std::shared_ptr<Texture> tex;
	std::shared_ptr<Mesh> mesh;
	std::string name;
};
