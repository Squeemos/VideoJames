#include "Sandbox.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"

#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/CameraFollow.h"
#include "../Components/RigidBody.h"

#include "../Systems/InputManager.h"

class Player
{

};

Sandbox::Sandbox()
{
	trace_message("Creating Sandbox Scene");

	camera = std::make_shared<Camera>();

	scene_name = "Sandbox";

	entt::entity e = registry.create();
	auto& tform = registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(200, 200), 0.0f, 2.0f);
	registry.emplace<RigidBody>(e, &tform);
	registry.emplace<CameraFollow>(e, camera);
	auto& mat = registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png", TextureType::Single));
	registry.emplace<Player>(e);

	entt::entity e2 = registry.create();
	registry.emplace<Transform>(e2, glm::vec2(600, 0.0f), glm::vec2(400, 400), 0.0f);
	auto& mat2 = registry.emplace<Material>(e2);
	mat2.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
}

Sandbox::~Sandbox()
{
	registry.clear();
}

void Sandbox::update(double& dt)
{
	float float_dt = static_cast<float>(dt);

	auto group = registry.group<Player, Transform>();
	for (auto [p, tform] : group.each())
	{
		//auto& tform = group.get<Transform>(p);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_W))
			tform.translate_y(400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_S))
			tform.translate_y(-400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_A))
			tform.translate_x(-400 * float_dt);
		if (InputManager::get_instance().check_key_held(GLFW_KEY_D))
			tform.translate_x(400 * float_dt);

		if (InputManager::get_instance().check_key_pressed(GLFW_KEY_UP))
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

	auto view = registry.view<RigidBody>();
	for (auto e : view)
	{
		view.get<RigidBody>(e).update(dt);
	}

	registry.view<CameraFollow, Transform>().each([](CameraFollow& cf, Transform& t)
		{
			cf.update(t.get_translation());
		}
	);

	if (InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse_world = camera->mouse_to_world(InputManager::get_instance().get_mouse_position());
		entt::entity e = registry.create();
		registry.emplace<Transform>(e, mouse_world, glm::vec2(200, 200), 0.0f, 2.0f);
		auto& mat = registry.emplace<Material>(e);
		mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
		mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgb_tex.jpg", TextureType::Single));
	}
}
