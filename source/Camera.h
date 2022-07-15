#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void update(double dt);
	glm::mat4 get_view();
	glm::mat4 get_projection();

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 size;
	float speed;
};