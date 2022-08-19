#include "SceneManager.h"
#include "Camera.h"

#include "../Components/Transform.h"
#include "../Components/Texture.h"
#include "../Components/Mesh.h"

#include "../Trace.h"

SceneManager::SceneManager() : changing_scene(false)
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

const entt::registry& SceneManager::get_renderables() const
{
	return current_scene->registry;
}

std::shared_ptr<Camera>& SceneManager::get_camera() const
{
	return current_scene->camera;
}

bool SceneManager::scene_changed() const
{
	return changing_scene;
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
	camera = std::make_shared<Camera>();

	entt::entity e = registry.create();
	registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(100, 100), 0.0f);
	registry.emplace<Texture>(e, "./assets/rgba_tex.png", "test");
	registry.emplace<Mesh>(e);

	e = registry.create();
	registry.emplace<Transform>(e, glm::vec2(1, 0), glm::vec2(100, 100), 45.0f);
	registry.emplace<Texture>(e, "./assets/rgb_tex.jpg", "tes2t");
	registry.emplace<Mesh>(e);

	e = registry.create();
	registry.emplace<Transform>(e, glm::vec2(0, 1), glm::vec2(100, 100), 45.0f);
	registry.emplace<Texture>(e, "./assets/rgb_tex.jpg", "tes2t");
	registry.emplace<Mesh>(e);
}

void SceneManager::Scene::update(double& dt)
{
	trace_message("Updating Scene: " + scene_name);
	dt;
}
