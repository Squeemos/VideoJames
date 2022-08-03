#include "SandboxScene.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Trace.h"
#include "Input.h"

// Components
#include "Name.h"
#include "Transform.h"
#include "Material.h"
#include "Scale.h"

#include "ModelManager.h"
#include "TextureManager.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>
#include <cstdlib>

static void add_to_registry_entity_name(entt::registry& reg, std::unordered_map<std::string, entt::entity>& map, const entt::entity& ent, const std::string& name)
{
	reg.emplace<Name>(ent, name);
	map[name] = ent;
}

SandboxScene::SandboxScene() : Scene()
{
	send_trace_message("Creating Sandbox Scene");

	// Add the camera
	camera = std::make_unique<Camera>();

	// Add entity to the registry, and add a material
	entt::entity entity = registry.create();
	auto& material = registry.emplace<Material>(entity);

	// Set all parts of the material
	material.shader = construct_shader("./data/simple_light.json");
	material.model = construct_model("./assets/backpack/backpack.obj");

	// Give the entity a name, transform, and scale
	registry.emplace<Transform>(entity, glm::vec3(0,2,0));
	registry.emplace<Scale>(entity, glm::vec3(1) * 1.5f);
	add_to_registry_entity_name(registry, entities_with_names, entity, "Backpack");
	

	entt::entity light = registry.create();
	registry.emplace<Transform>(light, glm::vec3(1));
	add_to_registry_entity_name(registry, entities_with_names, light, "Light");

	entt::entity capsule = registry.create();
	registry.emplace<Transform>(capsule, glm::vec3(0,10,0));
	registry.emplace<Scale>(capsule, glm::vec3(1) * 1.0f);
	auto& capsule_material = registry.emplace<Material>(capsule);
	capsule_material.shader = construct_shader("./data/simple_light.json");
	capsule_material.model = construct_model("./assets/capsule/capsule.obj");
	add_to_registry_entity_name(registry, entities_with_names, capsule, "Capsule");

	//// Do the same thing as above but add a shit ton of capsules
	//for (auto i = 0; i < 100; ++i)
	//{
	//	entt::entity e = registry.create();
	//	auto& m = registry.emplace<Material>(e);


	//	m.shader = construct_shader("./data/simple_3d.json");
	//	m.model = construct_model("./assets/capsule/capsule.obj");
	//	registry.emplace<Transform>(e, glm::vec3(1.0f * static_cast<float>(rand() % 10), 1.0f * static_cast<float>(rand() % 10), 1.0f * static_cast<float>(rand() % 10)));
	//}

}

SandboxScene::~SandboxScene()
{
	send_trace_message("Destroying Sandbox Scene");
}

void SandboxScene::update(double dt, glm::vec2& mouse)
{
	// Update the camera
	camera->update(dt, mouse);

	if (check_key(GLFW_KEY_P))
		registry.clear();
	// TODO: add in upadtes for all entities that need them


	auto& tform = registry.get<Transform>(entities_with_names["Light"]);
	float time = static_cast<float>(glfwGetTime());
	tform = glm::vec3(sinf(time), cosf(time), sinf(time) + cosf(time));
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

		// Set the camera uniforms (this will be changed with UBO)
		material.shader->set_mat4("projection", camera->get_projection());
		material.shader->set_vec3("viewPos", camera->get_position());
	
		// Set the view uniform
   		material.shader->set_mat4("view", camera->get_view());

		material.shader->set_bool("blinn", false);
		material.shader->set_vec3("lightPos", static_cast<glm::vec3>(registry.get<Transform>(entities_with_names["Light"])));

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