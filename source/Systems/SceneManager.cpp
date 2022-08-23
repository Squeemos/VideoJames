#include "SceneManager.h"
#include "Camera.h"

#include "MeshManager.h"
#include "TextureManager.h"

#include "../Trace.h"

static double total_time;

SceneManager::SceneManager() : changing_scene(false)
{
	total_time = 0;
	trace_message("Creating Scene Manager");

	scenes["Sandbox"] = std::make_shared<Scene>("Sandbox");
	scenes["Simple"] = std::make_shared<Scene>("Simple");

	current_scene = scenes["Sandbox"];
}

SceneManager::~SceneManager()
{
	trace_message("Destroying Scene Manager");
}

void SceneManager::update(double& dt)
{
	changing_scene = false;
	total_time += dt;
	if (total_time >= 2)
	{
		if(current_scene->scene_name == "Sandbox")
			change_scene("Simple");
		else if (current_scene->scene_name == "Simple")
			change_scene("Sandbox");

		changing_scene = true;
		total_time = 0;
		return;
	}
	current_scene->update(dt);
}

void SceneManager::change_scene(const std::string& scene_name)
{
	current_scene = scenes[scene_name];
}

RenderList SceneManager::get_renderables()
{
	return current_scene->registry.view<Transform, Material>();
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
	auto& mat = registry.emplace<Material>(e);
	mat.add_mesh(get_mesh("Simple Mesh"));
	mat.add_texture(get_texture("./assets/rgba_tex.png"));

	entt::entity e2 = registry.create();
	registry.emplace<Transform>(e2, glm::vec2(0.0f, 100.0f), glm::vec2(100, 100), 0.0f);
	auto& mat2 = registry.emplace<Material>(e2);
	mat2.add_mesh(get_mesh("Simple Mesh"));
	mat2.add_texture(get_texture("./assets/rgba_tex.png"));
}

void SceneManager::Scene::update(double& dt)
{
	trace_message("Updating Scene: " + scene_name);

	auto view = registry.view<Transform>();
	for (auto e : view)
	{
		auto& transform = view.get<Transform>(e);
		transform.rotate(static_cast<float>(dt) * 45);
	}
}
