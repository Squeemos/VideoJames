#include "Scene.h"
#include "Camera.h"

#include <iostream>

Scene::Scene()
{
	std::cout << "Creating Scene" << std::endl;
}

Scene::~Scene()
{
	std::cout << "Destroying Scene" << std::endl;
}

Camera& Scene::get_camera()
{
	return *camera;
}
