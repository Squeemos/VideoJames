#include "Camera.h"

#include "../Trace.h"

#include <string>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : position(0,0,3), target(0,0,-1), size(2560,1440), zoom(1.0f, 1.0f), near_clipping(.000001f), far_clipping(1000.0f), rotation(0.0f)
{
}

Camera::~Camera()
{
}

const glm::mat4 Camera::get_world_projection() const
{
	glm::vec2 proj_vec = glm::vec2(size.x * zoom.x, size.y * zoom.y) / 2.0f;
	return glm::ortho(-proj_vec.x, proj_vec.x, -proj_vec.y, proj_vec.y, near_clipping, far_clipping);
}

const glm::mat4 Camera::get_sceen_projection() const
{
	glm::vec2 proj_vec = size / 2.0f;
	return glm::ortho(-proj_vec.x, proj_vec.x, -proj_vec.y, proj_vec.y, near_clipping, far_clipping);
}

const glm::mat4 Camera::get_view() const
{
	return glm::lookAt(position, position + target, glm::vec3(0, 1.0f, 0));
}

const glm::mat4 Camera::get_rotation() const
{
	return glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1));
}

glm::vec2 Camera::mouse_to_world(const glm::vec2& mouse_screen) const
{
	float new_x = (mouse_screen.x * size.x * zoom.x) - ((size.x * zoom.x) / 2) + position.x;
	float new_y = (mouse_screen.y * size.y * zoom.y) - ((size.y * zoom.y) / 2) + position.y;
	return glm::vec2(new_x, new_y);
}

glm::vec2 Camera::mouse_to_screen(const glm::vec2& mouse_screen) const
{
	float new_x = size.x * (mouse_screen.x - 0.5f);
	float new_y = size.y * (mouse_screen.y - 0.5f);
	return glm::vec2(new_x, new_y);
}