#include "Camera.h"

#include "../Trace.h"
#include <string>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : position(0,0,3), target(0,0,-1), size(2560,1440), near_clipping(.000001f), far_clipping(1000.0f), rotation(0.0f)
{
}

Camera::~Camera()
{
}

const glm::mat4 Camera::get_projection_view() const
{
	// glm::mat4 projection = glm::mat4(1);
	glm::mat4 projection = glm::ortho(-size.x / 2.0f, size.x / 2.0f, -size.y / 2.0f, size.y / 2.0f, near_clipping, far_clipping);
	glm::mat4 view = glm::lookAt(position, position + target, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1));

	return projection * view * rotate;
}

glm::vec2 Camera::mouse_to_world(const glm::vec2& mouse_screen)
{
	float new_x = (mouse_screen.x * size.x) - (size.x / 2) + position.x;
	float new_y = (mouse_screen.y * size.y) - (size.y / 2) + position.y;
	return glm::vec2(new_x, new_y);
}
