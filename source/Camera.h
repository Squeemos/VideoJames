#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void update(double dt);

	glm::vec3 position;
	glm::vec3 target;
	float speed;
};