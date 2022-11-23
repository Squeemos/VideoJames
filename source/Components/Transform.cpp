#include "Transform.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : __translation(0,0), __scaling(100,100), __rotation(0.0f), __z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r) : __translation(t), __scaling(s), __rotation(r), __z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r, const float& z) : __translation(t), __scaling(s), __rotation(r), __z_order(z)
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::get_matrix() const
{
	glm::mat4 world = glm::mat4(1);
	world = glm::translate(world, glm::vec3(__translation.x, __translation.y, 0.0f));
	world = glm::rotate(world, glm::radians(__rotation), glm::vec3(0, 0, 0.1f));
	world = glm::scale(world, glm::vec3(__scaling, 1.0f));
	return world;
}