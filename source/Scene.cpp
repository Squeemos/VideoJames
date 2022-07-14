#include "Scene.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <iostream>

Scene::Scene() : camera(std::make_unique<Camera>()), ent(std::make_unique<Entity>(glm::vec2(0.0f, 0.0f), "./assets/rgba_tex.png", rgb_mode::rgba, "Kai'Sa"))
{
	std::cout << "Creating Scene" << std::endl;
}

Scene::~Scene()
{
	std::cout << "Destroying Scene" << std::endl;
}

void Scene::update(double dt)
{
	camera->update(dt);
	ent->update(dt);
}

Camera& Scene::get_camera()
{
	return *camera;
}
