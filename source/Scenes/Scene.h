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
	Scene() : camera(nullptr), shutdown(false), scene_finished(false) { }
	virtual ~Scene() {}
	virtual void update(double& dt) = 0;

	virtual void init() = 0;

protected:
	// Each scene at least has a name, camera, registry
	entt::registry registry;
	std::string scene_name;
	std::shared_ptr<Camera> camera;

	bool shutdown;
	bool scene_finished;
};

