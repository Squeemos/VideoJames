#include "SceneManager.h"
#include "Camera.h"

#include "../Scenes/Sandbox.h"

#include "../Trace.h"

SceneManager::SceneManager() : changing_scene(false)
{
	trace_message("Creating Scene Manager");

	std::shared_ptr<Scene> test = std::make_shared<Sandbox>();
	add_scene(test);
	change_scene(test->scene_name);
}

SceneManager::~SceneManager()
{
	trace_message("Destroying Scene Manager");
}

void SceneManager::update(double& dt)
{
	changing_scene = false;
	current_scene->update(dt);
}

void SceneManager::change_scene(const std::string& scene_name)
{
	current_scene = scenes[scene_name];
}

void SceneManager::add_scene(const std::shared_ptr<Scene>& scene)
{
	if (scene)
	{
		scenes.emplace(scene->scene_name, scene);
	}
}

RenderList SceneManager::get_renderables() const
{
	// Sort things by z_order
	const auto& view = current_scene->registry.view<const Transform, const Material>();
	// current_scene->registry.sort<Transform>(Transform::compare);

	return view;
}

std::shared_ptr<Camera>& SceneManager::get_camera() const
{
	return current_scene->camera;
}

bool SceneManager::scene_changed() const
{
	return changing_scene;
} 
