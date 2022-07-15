#include "SandboxScene.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <iostream>
#include <utility>

SandboxScene::SandboxScene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;
	set_camera(std::make_unique<Camera>());

	entity_list.push_back(std::make_unique<Entity>(glm::vec2(0.0f, 0.0f), "./assets/rgba_tex.png", rgb_mode::rgba, "Kai'Sa"));
}

SandboxScene::~SandboxScene()
{
	std::cout << "Destroying Sandbox Scene" << std::endl;
}

void SandboxScene::update(double dt)
{
	for (auto& e : entity_list)
	{
		e->update(dt);
	}
	get_camera().update(dt);
}

void SandboxScene::draw()
{
	for (auto& e : entity_list)
	{
		e->draw();
	}
}