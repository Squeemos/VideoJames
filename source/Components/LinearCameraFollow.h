#pragma once

#include "../Systems/Camera.h"

#include <glm/vec2.hpp>
#include <entt/entt.hpp>
#include <memory>


class LinearCameraFollow
{
public:
	LinearCameraFollow() : lerp_speed(1.0f) {}
	LinearCameraFollow(std::shared_ptr<Camera> cam) : camera(cam), lerp_speed(0.001f) {}
	~LinearCameraFollow() {}

	inline void add_camera(const std::shared_ptr<Camera> ptr) { camera = ptr; }
	void update(const glm::vec2& position);

private:
	std::shared_ptr<Camera> camera;
	float lerp_speed;
};