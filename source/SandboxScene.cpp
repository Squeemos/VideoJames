#include "SandboxScene.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Mesh.h"

#include <iostream>
#include <utility>

SandboxScene::SandboxScene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;
	set_camera(std::make_unique<Camera>());

	entity_list.push_back(std::make_unique<Entity>(glm::vec3(0.0f, 0.0f, 0.0f), "./assets/rgba_tex.png", rgb_mode::rgba, "Kai'Sa"));
	entity_list.push_back(std::make_unique<Entity>(glm::vec3(200.0f, 200.0f, 0.0f), "./assets/rgba_tex.png", rgb_mode::rgba, "Bagel"));
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

// This draws, but it draws late
void SandboxScene::draw()
{
	// bind shader program
	// set uniforms -> projection, view
	for (auto& e : entity_list)
	{
		// bind textures
		// optional: bind vbo
		// bind vao
		// set uniforms -> model
		// draw
		// unbind vao
		if (e->name == "Kai'Sa")
		{
			e->mesh->bind_shader_program();
			e->mesh->shader_set_mat4("projection", get_camera().get_projection());
			e->mesh->shader_set_mat4("view", get_camera().get_view());
			e->draw();
		}
		else
		{
			e->draw();
			e->mesh->unbind_shader_program();
		}
	}
}