#pragma once

#include "../Systems/Camera.h"

#include <glm/vec2.hpp>
#include <entt/entt.hpp>
#include <memory>


class CameraFollow
{
public:
	CameraFollow() {}
	CameraFollow(std::shared_ptr<Camera> cam) : camera(cam) {}
	~CameraFollow() {}

	inline void add_camera(const std::shared_ptr<Camera> ptr) { camera = ptr; }
	inline void update(const glm::vec2& position) { camera->set_translation(position); }

private:
	std::shared_ptr<Camera> camera;
};