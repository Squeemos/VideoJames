#include "Transform.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : translation(0,0), scaling(100,100), rotation(0.0f), z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r) : translation(t), scaling(s), rotation(r), z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r, const float& z) : translation(t), scaling(s), rotation(r), z_order(z)
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::get_world() const
{
	glm::mat4 world = glm::mat4(1);
	world = glm::translate(world, glm::vec3(translation, z_order));
	world = glm::rotate(world, glm::radians(rotation), glm::vec3(0, 0, 0.1f));
	world = glm::scale(world, glm::vec3(scaling, 1.0f));
	return world;
}