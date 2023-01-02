#include "Transform.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : __translation(0,0), __scaling(100,100), __rotation(0.0f), __z_order(0), __dirty(true), __matrix(1.0f)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r) : __translation(t), __scaling(s), __rotation(r), __z_order(0), __dirty(true), __matrix(1.0f)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r, const float& z) : __translation(t), __scaling(s), __rotation(r), __z_order(z), __dirty(true), __matrix(1.0f)
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::get_matrix()
{
	if (__dirty)
	{
		__matrix = glm::mat4(1.0f);
		__matrix = glm::translate(__matrix, glm::vec3(__translation.x, __translation.y, 0.0f));
		__matrix = glm::rotate(__matrix, glm::radians(__rotation), glm::vec3(0, 0, 0.1f));
		__matrix = glm::scale(__matrix, glm::vec3(__scaling, 1.0f));

		__dirty = false;
	}
	return __matrix;
}