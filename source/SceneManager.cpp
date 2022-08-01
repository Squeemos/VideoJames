#include "SceneManager.h"
#include "Scene.h"
#include "Trace.h"

#include "SandboxScene.h"

// Basically this thing will let us swap between scenes at some point
// that way we can load in scenes in another thread or something while still running the game to speed up loading

SceneManager::SceneManager()
{
	send_trace_message("Creating Scene Manager");

	current_scene = std::make_shared<SandboxScene>();
	add_scene(current_scene);
}

SceneManager::~SceneManager()
{
	send_trace_message("Destroying Scene Manager");
}


void SceneManager::update(double dt, glm::vec2& mouse)
{
	current_scene->update(dt, mouse);
}

void SceneManager::draw()
{
	current_scene->draw();
}

void SceneManager::add_scene(std::shared_ptr<Scene> scene)
{
	scenes.push_back(scene);
}
