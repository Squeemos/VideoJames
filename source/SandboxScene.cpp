#include "SandboxScene.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Model.h"

// Components
#include "Name.h"
#include "Transform.h"
#include "Material.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>
#include <cstdlib>

SandboxScene::SandboxScene() : Scene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;

	camera = std::make_unique<Camera>();

	// Add entity to the registry, and add a material
	entt::entity entity = registry.create();
	auto& material = registry.emplace<Material>(entity);

	// Set all parts of the material
	material.shader = construct_shader("./data/simple_3d.json");
	material.model = std::make_shared<Model>("./assets/1b1/1b1.obj");
	//material.texture = construct_texture("./assets/rgba_tex.png", rgb_mode::rgba);

	// Give the entity a name and transform
	registry.emplace<Name>(entity, "Teapot");
	registry.emplace<Transform>(entity);
}

SandboxScene::~SandboxScene()
{
	std::cout << "Destroying Sandbox Scene" << std::endl;
}

void SandboxScene::update(double dt, glm::vec2& mouse)
{
	camera->update(dt, mouse);
}

// This might be able to be moved into the base scene class
void SandboxScene::draw()
{
	//// Create a group with all entities with a transform and a material (therefore, renderable)
	//auto group = registry.group<Transform>(entt::get<Material>);
	//for (auto& entity : group)
	//{
	//	// Get the transform and the material of the current entity
	//	const auto& [transform, material] = group.get<Transform, Material>(entity);

	//	// This is the render loop

	//	// Use the shader
	//	material.shader->use();

	//	// Set the camera uniforms
 //		material.shader->set_mat4("projection", camera->get_projection());

 //		auto view = camera->get_view();
	//	material.shader->set_mat4("view", view);

	//	// Set the transform uniform
	//	glm::mat4 model = glm::mat4(1);
	//	model = glm::translate(model, static_cast<glm::vec3>(transform)); // <- I think there's a way to just use transform since it should be able to convert?
	//	material.shader->set_mat4("model", model);
	//	
	//	// Prep the texture
	//	material.shader->set_int("texture0", 0);

	//	// If the material has a texture
	//	//if (material.texture)
	//	//{
	//	//	// Set the uniform to use the texture and bind it
	//	//	material.shader->set_int("texture_or_color", 1);
	//	//	material.texture->bind();
	//	//}
	//	//else
	//	//{
	//	//	// Set the uniform to use the color of the vertices
	//	//	material.shader->set_int("texture_or_color", 0);
	//	//}

	//	material.shader->set_int("texture_or_color", 0);

	//	// Bind the mesh
	//	//material.mesh->bind_vao();

	//	// Unbind the mesh
	//	//material.mesh->unbind_vao();

	//	// If there's a texture, unbind the texture
	//	//if(material.texture)
	//	//	material.texture->unbind();
	//	
	//	// Unbind the shader
	//	material.shader->unbind();
	//}

	auto group = registry.group<Transform>(entt::get<Material>);
	for (auto& entity : group)
	{
		const auto& [transform, material] = group.get<Transform, Material>(entity);

		material.shader->use();
		

		// Set the camera uniforms
		material.shader->set_mat4("projection", camera->get_projection());

		auto view = camera->get_view();
   		material.shader->set_mat4("view", view);

   		// Set the transform uniform
   		glm::mat4 model = glm::mat4(1);
   		model = glm::translate(model, static_cast<glm::vec3>(transform)); // <- I think there's a way to just use transform since it should be able to convert?
   		material.shader->set_mat4("model", model);
   	
		Shader& shad = *material.shader;
		material.model->draw(shad);
		material.shader->unbind();
	}
}