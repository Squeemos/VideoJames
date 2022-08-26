#include "Sandbox.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"

#include "../Components/Transform.h"
#include "../Components/Material.h"

#include "../Systems/InputManager.h"

Sandbox::Sandbox()
{
	trace_message("Creating Sandbox Scene");
	scene_name = "Sandbox";

	camera = std::make_shared<Camera>();

	entt::entity e = registry.create();
	registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(100, 100), 0.0f);
	auto& mat = registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("Simple Mesh"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png"));
}

Sandbox::~Sandbox()
{
}

void Sandbox::update(double& dt)
{
	float float_dt = static_cast<float>(dt);

	// Very simple update with some movement control
	auto view = registry.view<Transform>();
	for (auto e : view)
	{
		auto& transform = view.get<Transform>(e);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_W))
			transform.translate_y(100 * float_dt);
		if(InputManager::get_instance().check_key_held(GLFW_KEY_S))
			transform.translate_y(-100 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_A))
			transform.translate_x(-100 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_D))
			transform.translate_x(100 * float_dt);
	}
}
