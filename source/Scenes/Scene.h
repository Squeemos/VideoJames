#pragma once

#include <entt/entt.hpp>
#include "../Systems/Camera.h"

class SceneManager;

class Scene
{
	friend SceneManager;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void update(double& dt) = 0;

protected:
	entt::registry registry;
	std::string scene_name;
	std::shared_ptr<Camera> camera;
};

