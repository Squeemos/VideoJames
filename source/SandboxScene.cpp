#include "SandboxScene.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Trace.h"

// Components
#include "Name.h"
#include "Transform.h"
#include "Material.h"
#include "ModelManager.h"
#include "Scale.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>
#include <cstdlib>

SandboxScene::SandboxScene() : Scene()
{
	send_trace_message("Creating Sandbox Scene");

	// Add the camera
	camera = std::make_unique<Camera>();

	// Add entity to the registry, and add a material
	entt::entity entity = registry.create();
	auto& material = registry.emplace<Material>(entity);

	// Set all parts of the material
	material.shader = construct_shader("./data/simple_3d.json");
	material.model = construct_model("./assets/backpack/backpack.obj");
	//material.texture = construct_texture("./assets/rgba_tex.png", rgb_mode::rgba);

	// Give the entity a name, transform, and scale
	registry.emplace<Name>(entity, "Capsule");
	registry.emplace<Transform>(entity, glm::vec3(-10, -10, 0));
	registry.emplace<Scale>(entity, glm::vec3(1) * .2f);
	

	// Do the same thing as above but add a shit ton of capsules
	for (auto i = 0; i < 100; ++i)
	{
		entt::entity e = registry.create();
		auto& m = registry.emplace<Material>(e);


		m.shader = construct_shader("./data/simple_3d.json");
		m.model = construct_model("./assets/capsule/capsule.obj");
		registry.emplace<Name>(e, "Clone");
		registry.emplace<Transform>(e, glm::vec3(1.0f * static_cast<float>(rand() % 10), 1.0f * static_cast<float>(rand() % 10), 1.0f * static_cast<float>(rand() % 10)));
	}
}

SandboxScene::~SandboxScene()
{
	send_trace_message("Destroying Sandbox Scene");
}

void SandboxScene::update(double dt, glm::vec2& mouse)
{
	// Update the camera
	camera->update(dt, mouse);

	// TODO: add in upadtes for all entities that need them
}

// This might be able to be moved into the base scene class
void SandboxScene::draw()
{
	// Create group of entities that all have a transform and a material
	auto group = registry.group<Transform>(entt::get<Material>);
	for (auto& entity : group)
	{
		// Get the transform and material
		const auto& [transform, material] = group.get<Transform, Material>(entity);

		// Use the shader of the material
		material.shader->use();

		// Set the camera uniforms
		material.shader->set_mat4("projection", camera->get_projection());
	
		// Set the view uniform
   		material.shader->set_mat4("view", camera->get_view());

   		// Set the transform uniform
   		glm::mat4 model = glm::mat4(1);

		// Check if the entity has a scale component, and if it does, scale the model
		if (registry.all_of<Scale>(entity))
		{
			model = glm::scale(model, static_cast<glm::vec3>(registry.get<Scale>(entity)));
		}

		// Translate the model into world space and set the uniform
   		model = glm::translate(model, static_cast<glm::vec3>(transform)); // <- I think there's a way to just use transform since it should be able to convert?
   		material.shader->set_mat4("model", model);
   	
		// Draw
		material.model->draw(*material.shader);

		// Unbind so we clean everything up
		material.shader->unuse();
	}
}