#pragma once

#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	const glm::mat4 get_projection_view() const;

	const glm::mat4 get1() const;
	const glm::mat4 get2() const;

private:
	glm::vec3 position, target;
	glm::vec2 size;
	float near_clipping, far_clipping;
	float rotation;
};

