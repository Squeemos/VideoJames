#pragma once

#include "../Systems/Camera.h"

#include <entt/entt.hpp>
#include <unordered_map>

class SceneManager;

// ABC for scenes
class Scene
{
public:

	// All virtual methods that need to be created for scenes to work
	Scene() : __camera(nullptr), __scene_manager(nullptr), __shutdown(false), __scene_finished(false) {}
	Scene(SceneManager* scene_manager) : __camera(nullptr), __scene_manager(scene_manager), __shutdown(false), __scene_finished(false) {}
	virtual ~Scene() {}

	virtual void update(double& dt) = 0;
	virtual void init() = 0;

	virtual const std::string& get_name() { return __scene_name; }
	virtual entt::registry& get_registry() { return __registry; }
	virtual std::shared_ptr<Camera> get_camera() { return __camera; }
	virtual bool get_finished() { return __scene_finished; }
	virtual bool get_shutdown() { return __shutdown; }

protected:
	// Each scene at least has a name, camera, registry
	entt::registry __registry;
	std::string __scene_name;
	std::shared_ptr<Camera> __camera;
	SceneManager* __scene_manager;

	bool __shutdown;
	bool __scene_finished;
};

