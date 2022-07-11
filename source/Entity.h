#pragma once
#include <utility>
#include "glm/vec2.hpp"

class Entity
{
public:
	Entity();
	~Entity();
	void draw();
	void update(double dt);

	glm::vec2 position;
};

