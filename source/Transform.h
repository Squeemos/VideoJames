#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	Transform() : position(0.0f, 0.0f, 0.0f) {}
	Transform(glm::vec3 tform) : position(tform) {}
	~Transform() {}

	operator glm::vec3() { return position; }
	operator glm::vec3& () { return position; }
	operator const glm::vec3& () const { return position; }

private:
	glm::vec3 position;
};