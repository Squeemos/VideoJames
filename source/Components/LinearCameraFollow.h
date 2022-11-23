#pragma once

#include "../Systems/Camera.h"

#include <glm/vec2.hpp>
#include <entt/entt.hpp>
#include <memory>


class LinearCameraFollow
{
public:
	LinearCameraFollow() : __lerp_speed(1.0f) {}
	LinearCameraFollow(std::shared_ptr<Camera> cam) : __camera(cam), __lerp_speed(1.0f) {}
	LinearCameraFollow(std::shared_ptr<Camera> cam, float speed) : __camera(cam), __lerp_speed(speed) {}
	~LinearCameraFollow() {}

	inline void add_camera(const std::shared_ptr<Camera> ptr) { __camera = ptr; }
	void update(const glm::vec2& position);

private:
	std::shared_ptr<Camera> __camera;
	float __lerp_speed;
};