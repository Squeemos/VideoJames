#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

#include <iostream>

SceneManager::SceneManager()
{
	std::cout << "Creating Scene Manager" << std::endl;

	current_scene = std::make_shared<Scene>();
	add_scene(current_scene);
}

SceneManager::~SceneManager()
{
	std::cout << "Destorying Scene Manager" << std::endl;
}


void SceneManager::update(double dt)
{
	current_scene->update(dt);
}

void SceneManager::add_scene(std::shared_ptr<Scene> scene)
{
	scenes.push_back(scene);
}

std::shared_ptr<Scene> SceneManager::get_current_scene()
{
	return current_scene;
}

Camera& SceneManager::get_current_camera()
{
	return current_scene->get_camera();
}
