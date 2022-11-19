#include "Sandbox.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"

#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/LinearCameraFollow.h"
#include "../Components/RigidBody.h"
#include "../Components/RenderTag.h"
#include "../Components/Gui.h"

#include "../Systems/InputManager.h"

class Player
{

};

Sandbox::Sandbox()
{
	trace_message("Creating Sandbox Scene");

	camera = std::make_shared<Camera>();

	scene_name = "Sandbox";

	init();
}

Sandbox::~Sandbox()
{
	registry.clear();
}

void Sandbox::update(double& dt)
{
	float float_dt = static_cast<float>(dt);

	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_R))
	{
		init();
		return;
	}


	auto player_view = registry.view<Player, Transform>();
	for (auto [p, tform] : player_view.each())
	{
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

	for (auto [e, rb] : registry.view<RigidBody>().each())
	{
		rb.update(dt);
	}

	registry.view<LinearCameraFollow, Transform>().each([](LinearCameraFollow& cf, Transform& t)
		{
			cf.update(t.get_translation());
		}
	);

	if (InputManager::get_instance().check_mouse_held(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 mouse_world = camera->mouse_to_world(InputManager::get_instance().get_mouse_position());
		entt::entity e = registry.create();
		registry.emplace<Transform>(e, mouse_world, glm::vec2(200, 200), 0.0f, 2.0f);
		auto& mat = registry.emplace<Material>(e);
		mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
		mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgb_tex.jpg", TextureType::Single));
		registry.emplace<RenderTag>(e, RenderType::World);
	}

	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_5))
		camera->reset_zoom();
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_8))
		camera->zoom_y(-.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_2))
		camera->zoom_y(.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_4))
		camera->zoom_x(-.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_6))
		camera->zoom_x(.001f);

	for (auto [e, ge] : registry.view<GuiContainer>().each())
	{
		ge.update();
	}
}

void Sandbox::init()
{
	registry.clear();

	entt::entity e = registry.create();
	auto& tform = registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(200, 200), 0.0f, 2.0f);
	registry.emplace<RigidBody>(e, &tform);
	registry.emplace<LinearCameraFollow>(e, camera, 1.0f);
	auto& mat = registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png", TextureType::Single));
	registry.emplace<Player>(e);
	registry.emplace<RenderTag>(e, RenderType::World);

	entt::entity e2 = registry.create();
	registry.emplace<Transform>(e2, glm::vec2(600, 0.0f), glm::vec2(400, 400), 0.0f);
	auto& mat2 = registry.emplace<Material>(e2);
	mat2.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	registry.emplace<RenderTag>(e2, RenderType::World);

	entt::entity e3 = registry.create();
	registry.emplace<Transform>(e3, glm::vec2(-1230.0f, 670.0f), glm::vec2(100.0f, 100.0f), 0.0f, 4.0f);
	auto& mat3 = registry.emplace<Material>(e3);
	mat3.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat3.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/x.png", TextureType::Single));
	registry.emplace<RenderTag>(e3, RenderType::Screen);
	auto& gc = registry.emplace<GuiContainer>(e3);
	gc.add_element(std::make_shared<ExitButton>(&shutdown));
}
