#include "Camera.h"

#include "../Trace.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : position(0,0,3), target(0,0,-1), size(1280,720), near_clipping(.0001f), far_clipping(1000.0f), rotation(0.0f)
{
}

Camera::~Camera()
{
}

const glm::mat4 Camera::get_projection_view() const
{
	glm::mat4 projection = glm::ortho(position.x - (size.x / 2.0f), position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.y + (size.y / 2.0f), near_clipping, far_clipping);
	glm::mat4 view = glm::lookAt(position, position + target, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1));

	return projection * view * rotate;
}

void Camera::translate(const glm::vec2& direction)
{
	position.x += direction.x;
	position.y += direction.y;
}

void Camera::rotate(const float& degrees)
{
	rotation += degrees;
}
