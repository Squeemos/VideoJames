#pragma once

#include <entt/entt.hpp>
#include "../Systems/Camera.h"

class SceneManager;

// ABC for scenes
class Scene
{
	// This way the scene manager can access the registry/name/camera
	friend SceneManager;
public:

	// All virtual methods that need to be created for scenes to work
	Scene() { camera = std::make_shared<Camera>(); }
	virtual ~Scene() {}
	virtual void update(double& dt) = 0;

protected:
	// Each scene at least has a name, camera, and registry
	entt::registry registry;
	std::string scene_name;
	std::shared_ptr<Camera> camera;
};

