#include "SceneManager.h"

#include "../Components/Transform.h"

#include "../Trace.h"

SceneManager::SceneManager()
{
	trace_message("Creating Scene Manager");

	current_scene = std::make_shared<Scene>("Sandbox");

	scenes["Sandbox"] = current_scene;
}

SceneManager::~SceneManager()
{
	trace_message("Destroying Scene Manager");
}

void SceneManager::update(double& dt)
{
	current_scene->update(dt);
}

const auto& SceneManager::get_renderables() const
{
	return current_scene->registry.view<Transform>();
}

SceneManager::Scene::Scene()
{
}

SceneManager::Scene::~Scene()
{
	trace_message("Destroying Scene: " + scene_name);
}

SceneManager::Scene::Scene(const std::string& name) : scene_name(name)
{
	trace_message("Creating Scene: " + name);
}

void SceneManager::Scene::update(double& dt)
{
	trace_message("Updating Scene: " + scene_name);
	dt;
}
