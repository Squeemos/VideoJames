#include "LinearCameraFollow.h"
#include <cmath>

void LinearCameraFollow::update(const glm::vec2& position)
{
	glm::vec2 camera_pos = camera->get_position();
	glm::vec2 diff = glm::vec2(position.x - camera_pos.x, position.y - camera_pos.y);
	diff *= lerp_speed;

	camera->set_translation(camera_pos + diff);
}
