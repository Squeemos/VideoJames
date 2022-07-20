#include "SandboxScene.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>

SandboxScene::SandboxScene() : Scene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;

	camera = std::make_unique<Camera>();

	entt::entity entity = registry.create();
	registry.emplace<Shader>(entity, "./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");
	// registry.emplace<Mesh>(entity);
	// std::make_unique<Entity>(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(-z)), "./assets/rgba_tex.png", rgb_mode::rgba, "Kai'Sa");
}

SandboxScene::~SandboxScene()
{
	std::cout << "Destroying Sandbox Scene" << std::endl;
}

void SandboxScene::update(double dt)
{
	camera->update(dt);
}

// This draws, but it draws late
void SandboxScene::draw()
{
	//// Ideally move the shit to outside the iteration
	//for (auto& e : entity_list)
	//{
	//	// bind shader program
	//	e->shader->use();
	//	// set uniforms -> projection, view
	//	e->shader->set_mat4("projection", camera->get_projection());
	//	e->shader->set_mat4("view", camera->get_view());
	//	// bind textures
	//	// optional: bind vbo
	//	// bind vao
	//	// set uniforms -> model
	//	e->shader->set_mat4("model", e->draw());
	//	e->shader->set_int("texture0", 0);
	//	// draw
	//	// unbind vao
	//	// Use the texture
	//	e->tex->use();
	//	e->mesh->bind_vao();
	//	// Unbind the mesh
	//	e->mesh->unbind_vao();
	//}

	// Find a group with transforms and meshes
	//auto group = registry.group<Shader>();
	//for (auto entity : group)
	//{
	//	auto shader = group.get<Shader>(entity);
	//}

	//auto view = registry.view<Shader>();
	//for (auto& entity : view)
	//{
	//	auto& shader = view.get<Shader>(entity);
	//	shader.use();
	//	shader.unbind();
	//}
}