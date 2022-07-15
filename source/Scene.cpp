#include "Scene.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <iostream>

Scene::Scene()
{
	std::cout << "Creating Scene" << std::endl;
}

Scene::~Scene()
{
	std::cout << "Destroying Scene" << std::endl;
}

void Scene::update(double dt)
{
	dt;
}

void Scene::draw()
{
}

void Scene::set_camera(std::unique_ptr<Camera> cam)
{
	camera = std::move(cam);
}

Camera& Scene::get_camera()
{
	return *camera;
}
