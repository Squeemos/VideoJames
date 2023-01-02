#include "SceneManager.h"
#include "Camera.h"

#include "../Scenes/Sandbox.h"
#include "../Scenes/MainMenu.h"

#include "../Trace.h"

SceneManager::SceneManager() : __changing_scene(false)
{
	trace_message("Creating Scene Manager");

	std::shared_ptr<Scene> main_menu = std::make_shared<MainMenu>(this);
	std::shared_ptr<Scene> sandbox = std::make_shared<Sandbox>(this);

	add_scene(main_menu);
	add_scene(sandbox);

	change_scene(main_menu->get_name());
}

SceneManager::~SceneManager()
{
	trace_message("Destroying Scene Manager");
}

void SceneManager::update(double& dt)
{
	__current_scene->update(dt);
}

void SceneManager::change_scene(const std::string& scene_name)
{
	trace_message("Changing Scene: " + scene_name);
	__current_scene = __scenes[scene_name];
}

void SceneManager::add_scene(const std::shared_ptr<Scene>& scene)
{
	if (scene)
	{
		__scenes.emplace(scene->get_name(), scene);
	}
}

RenderList SceneManager::get_renderables() const
{
	// Sort things by z_order
	__current_scene->get_registry().sort<Transform>(Transform::compare);

	return __current_scene->get_registry().view<render_components>();
}

std::shared_ptr<Camera> SceneManager::get_camera() const
{
	return __current_scene->get_camera();
}

bool SceneManager::finished() const
{
	return __current_scene->get_finished();
}

bool SceneManager::shutdown() const
{
	return __current_scene->get_shutdown();
}