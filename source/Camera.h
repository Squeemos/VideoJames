#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void update(double dt, glm::vec2& vector);
	glm::mat4 get_view();
	glm::mat4 get_projection();
	glm::vec3 get_position();

private:
	glm::vec3 position, target, size;
	glm::vec2 mouse, rotation;
	float speed;
};