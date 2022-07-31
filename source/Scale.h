#pragma once

#include <glm/glm.hpp>

class Scale
{
public:
	Scale() : sc(1.0f, 1.0f, 1.0f) {}
	Scale(glm::vec3 s) : sc(s) {}
	~Scale() {}

	operator glm::vec3& () { return sc; }
	operator const glm::vec3& () const { return sc; }

private:
	glm::vec3 sc;
};