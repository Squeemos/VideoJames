#include "Camera.h"

#include "../Trace.h"

#include <string>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : __position(0,0,3), __target(0,0,-1), __size(2560,1440), __zoom(1.0f, 1.0f), __near_clipping(.000001f), __far_clipping(1000.0f), __rotation(0.0f)
{
}

Camera::~Camera()
{
}

const glm::mat4 Camera::get_world_projection() const
{
	glm::vec2 proj_vec = glm::vec2(__size.x * __zoom.x, __size.y * __zoom.y) / 2.0f;
	return glm::ortho(-proj_vec.x, proj_vec.x, -proj_vec.y, proj_vec.y, __near_clipping, __far_clipping);
}

const glm::mat4 Camera::get_sceen_projection() const
{
	glm::vec2 proj_vec = __size / 2.0f;
	return glm::ortho(-proj_vec.x, proj_vec.x, -proj_vec.y, proj_vec.y, __near_clipping, __far_clipping);
}

const glm::mat4 Camera::get_view() const
{
	return glm::lookAt(__position, __position + __target, glm::vec3(0, 1.0f, 0));
}

const glm::mat4 Camera::get_rotation() const
{
	return glm::rotate(glm::mat4(1), glm::radians(__rotation), glm::vec3(0, 0, 1));
}

glm::vec2 Camera::mouse_to_world(const glm::vec2& mouse_screen) const
{
	float new_x = (mouse_screen.x * __size.x * __zoom.x) - ((__size.x * __zoom.x) / 2) + __position.x;
	float new_y = (mouse_screen.y * __size.y * __zoom.y) - ((__size.y * __zoom.y) / 2) + __position.y;
	return glm::vec2(new_x, new_y);
}

glm::vec2 Camera::mouse_to_screen(const glm::vec2& mouse_screen) const
{
	float new_x = __size.x * (mouse_screen.x - 0.5f);
	float new_y = __size.y * (mouse_screen.y - 0.5f);
	return glm::vec2(new_x, new_y);
}