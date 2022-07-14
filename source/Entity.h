#pragma once
#include <utility>
#include <memory>
#include <string>
#include <glm/glm.hpp>

class Texture;
enum class rgb_mode;

class Entity
{
public:
	Entity();
	Entity(glm::vec2 new_pos, const std::string& texture, rgb_mode mode);
	~Entity();
	void draw();
	void update(double dt);

	glm::vec2 position;
	glm::vec2 scale;
	glm::vec3 rotation;
	std::unique_ptr<Texture> tex;
};

