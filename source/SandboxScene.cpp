#include "SandboxScene.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <iostream>
#include <utility>

SandboxScene::SandboxScene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;
	set_camera(std::make_unique<Camera>());

	entity_list.push_back(std::make_unique<Entity>(glm::vec3(0.0f, 0.0f, 0.0f), "./assets/rgba_tex.png", rgb_mode::rgba, "Kai'Sa"));
	entity_list.push_back(std::make_unique<Entity>(glm::vec3(10.0f, 0.0f, -5.0f), "./assets/rgb_tex.jpg", rgb_mode::rgb, "Eagle"));
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
	camera->update(dt);
}

// This draws, but it draws late
void SandboxScene::draw()
{
	// Ideally move the shit to outside the iteration
	for (auto& e : entity_list)
	{
		// bind shader program
		e->shader->use();
		// set uniforms -> projection, view
		e->shader->set_mat4("projection", camera->get_projection());
		e->shader->set_mat4("view", camera->get_view());
		// bind textures
		// optional: bind vbo
		// bind vao
		// set uniforms -> model
		e->shader->set_mat4("model", e->draw());
		e->shader->set_int("texture0", 0);
		// draw
		// unbind vao
		// Use the texture
		e->tex->use();
		e->mesh->bind_vao();
		// Unbind the mesh
		e->mesh->unbind_vao();
	}
}