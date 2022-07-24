#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

#include "SandboxScene.h"

#include <iostream>

SceneManager::SceneManager()
{
	std::cout << "Creating Scene Manager" << std::endl;

	current_scene = std::make_shared<SandboxScene>();
	add_scene(current_scene);
}

SceneManager::~SceneManager()
{
	std::cout << "Destorying Scene Manager" << std::endl;
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
