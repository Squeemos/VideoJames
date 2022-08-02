#pragma once

#include <glm/glm.hpp>

#include <string>

class Transform
{
public:
	Transform() : position(0.0f, 0.0f, 0.0f) {}
	Transform(glm::vec3 tform) : position(tform) {}
	~Transform() {}

	operator glm::vec3& ()
	{ 
		return position;
	}
	operator const glm::vec3& () const 
	{
		return position;
	}

	Transform& operator+= (glm::vec3 other)
	{
		position += other;
		return *this;
	}

	Transform& operator*= (float other)
	{
		position *= other;
		return *this;
	}

private:
	glm::vec3 position;
};