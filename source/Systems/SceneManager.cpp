#include "SceneManager.h"
#include "Camera.h"

#include "../Scenes/Sandbox.h"

#include "../Trace.h"

SceneManager::SceneManager() : __changing_scene(false)
{
	trace_message("Creating Scene Manager");

	std::shared_ptr<Scene> test = std::make_shared<Sandbox>();
	add_scene(test);
	change_scene(test->__scene_name);
}

SceneManager::~SceneManager()
{
	trace_message("Destroying Scene Manager");
}

void SceneManager::update(double& dt)
{
	__changing_scene = false;
	__current_scene->update(dt);
}

void SceneManager::change_scene(const std::string& scene_name)
{
	__current_scene = __scenes[scene_name];
}

void SceneManager::add_scene(const std::shared_ptr<Scene>& scene)
{
	if (scene)
	{
		__scenes.emplace(scene->__scene_name, scene);
	}
}

RenderList SceneManager::get_renderables() const
{
	// Sort things by z_order
	__current_scene->__registry.sort<Transform>(Transform::compare);

	return __current_scene->__registry.view<const Transform, const Material, const RenderTag>();
}

std::shared_ptr<Camera>& SceneManager::get_camera() const
{
	return __current_scene->__camera;
}

bool SceneManager::scene_changed() const
{
	return __changing_scene;
} 

bool SceneManager::finished() const
{
	return __current_scene->__scene_finished;
}

bool SceneManager::shutdown() const
{
	return __current_scene->__shutdown;
}