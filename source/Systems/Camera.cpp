#include "Camera.h"

#include "../Trace.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : position(0,0,3), target(0,0,-1), size(2560,1440), near_clipping(.0001f), far_clipping(1000.0f), rotation(0.0f)
{
}

Camera::~Camera()
{
}

const glm::mat4 Camera::get_projection_view() const
{
	glm::mat4 projection = glm::ortho(-size.x / 2.0f, size.x / 2.0f, -size.y / 2.0f, size.y / 2.0f, near_clipping, far_clipping);
	glm::mat4 view = glm::lookAt(position, position + target, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1));

	return projection * view * rotate;
}
