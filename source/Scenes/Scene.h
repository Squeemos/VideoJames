#pragma once

#include "../Systems/Camera.h"

#include <entt/entt.hpp>
#include <unordered_map>

class SceneManager;

// ABC for scenes
class Scene
{
	// This way the scene manager can access the registry/name/camera
	friend SceneManager;
public:

	// All virtual methods that need to be created for scenes to work
	Scene() { }
	virtual ~Scene() {}
	virtual void update(double& dt) = 0;

protected:
	// Each scene at least has a name, camera, registry, and map
	entt::registry registry;
	std::string scene_name;
	std::shared_ptr<Camera> camera;
	std::unordered_map<std::string, entt::entity> entities_map;
};

