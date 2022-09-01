#include "Sandbox.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"

#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/CameraFollow.h"

#include "../Systems/InputManager.h"

Sandbox::Sandbox()
{
	trace_message("Creating Sandbox Scene");

	camera = std::make_shared<Camera>();

	scene_name = "Sandbox";

	entt::entity e = registry.create();
	registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(400, 400), 0.0f, 0.0f);
	registry.emplace<CameraFollow>(e, camera);
	auto& mat = registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png", TextureType::Single));
	entities_map.try_emplace("Player1", e);

	entt::entity e2 = registry.create();
	registry.emplace<Transform>(e2, glm::vec2(400, 0.0f), glm::vec2(400, 400), 0.0f, -1.0f);
	auto& mat2 = registry.emplace<Material>(e2);
	mat2.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	entities_map.try_emplace("Player2", e2);

	entt::entity e3 = registry.create();
	registry.emplace<Transform>(e3, glm::vec2(-400, 0.0f), glm::vec2(400, 400), 0.0f, 1.0f);
	auto& mat3 = registry.emplace<Material>(e3);
	mat3.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat3.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgb_tex.jpg", TextureType::Single));
	entities_map.try_emplace("Player3", e3);
}

Sandbox::~Sandbox()
{
	registry.clear();
}

void Sandbox::update(double& dt)
{
	float float_dt = static_cast<float>(dt);

	auto player = entities_map.find("Player1");
	if (player != entities_map.end())
	{
		auto& tform = registry.get<Transform>(player->second);

		if (InputManager::get_instance().check_key_held(GLFW_KEY_W))
			tform.translate_y(400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_S))
			tform.translate_y(-400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_A))
			tform.translate_x(-400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_D))
			tform.translate_x(400 * float_dt);

		if(InputManager::get_instance().check_key_pressed(GLFW_KEY_UP))
			tform.set_z_order(2.0f);
		if (InputManager::get_instance().check_key_pressed(GLFW_KEY_DOWN))
			tform.set_z_order(-2.0f);

		if (InputManager::get_instance().check_key_held(GLFW_KEY_Q))
			tform.rotate(90 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_E))
			tform.rotate(-90 * float_dt);

		if (InputManager::get_instance().check_key_held(GLFW_KEY_LEFT))
			tform.scale(-100 * float_dt, -100 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_RIGHT))
			tform.scale(100 * float_dt, 100 * float_dt);
	}

	registry.view<CameraFollow, Transform>().each([](CameraFollow& cf, const Transform& t)
		{
			cf.update(t.get_translation());
		});
}
