#include "Sandbox.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"

#include "../Components/Player.h"
#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/LinearCameraFollow.h"
#include "../Components/RigidBody.h"
#include "../Components/RenderTag.h"
#include "../Components/Gui.h"
#include "../Components/Collision.h"

#include "../Systems/InputManager.h"

Sandbox::Sandbox()
{
	trace_message("Creating Sandbox Scene");

	__camera = std::make_shared<Camera>();

	__scene_name = "Sandbox";

	init();
}

Sandbox::~Sandbox()
{
	__registry.clear();
}

void Sandbox::update(double& dt)
{
	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_R))
	{
		init();
		return;
	}

	__registry.view<RigidBody, Transform>().each([&dt](auto e, auto& rb, auto& tform)
		{
			e;
			rb.update(dt, tform);
		}
	);

	__registry.view<Player, Transform>().each([&dt](auto e, auto& player, auto& tform)
		{
			e;
			player.update(dt, tform);
		}
	);

	__registry.view<Player, Collider>().each([&dt](auto e, auto& player, auto& collider)
		{
			e;
			player;
			collider;
		}
	);

	__registry.view<LinearCameraFollow, Transform>().each([](auto e, auto& cf, auto& tform)
		{
			e;
			cf.update(tform.get_translation());
		}
	);

	if (InputManager::get_instance().check_mouse_held(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 mouse_world = __camera->mouse_to_world(InputManager::get_instance().get_mouse_position());
		auto e = __registry.create();
		__registry.emplace<Transform>(e, mouse_world, glm::vec2(200, 200), 0.0f, 2.0f);
		auto& mat = __registry.emplace<Material>(e);
		mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
		mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgb_tex.jpg", TextureType::Single));
		__registry.emplace<RenderTag>(e, RenderType::World);
	}

	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_5))
		__camera->reset_zoom();
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_8))
		__camera->zoom_y(-.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_2))
		__camera->zoom_y(.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_4))
		__camera->zoom_x(-.001f);
	if (InputManager::get_instance().check_key_held(GLFW_KEY_KP_6))
		__camera->zoom_x(.001f);

	__registry.view<GuiContainer>().each([](auto e, auto& ge)
		{
			e;
			ge.update();
		}
	);

	auto view = __registry.view<Collider, Transform>();
	for (auto first = view.begin(); first != view.end(); ++first)
	{
		for (auto second = std::next(first); second != view.end(); ++second)
		{
			auto& first_collider = view.get<Collider>(*first);
			auto& second_collider = view.get<Collider>(*second);
			
			auto& first_tform = view.get<Transform>(*first);
			auto& second_tform = view.get<Transform>(*second);

			CollisionInfo info = Collider::check_collision(first_collider, first_tform, second_collider, second_tform);
			if (info.collided)
			{
				__registry.get<Material>(*first).add_color(glm::vec3(0.0f, 1.0f, 0.0f));
				__registry.get<Material>(*second).add_color(glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else
			{
				__registry.get<Material>(*first).add_color(glm::vec3(1.0f, 0.0f, 0.0f));
				__registry.get<Material>(*second).add_color(glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}
	}
}

void Sandbox::init()
{
	__registry.clear();

	auto e = __registry.create();
	__registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f), 45.0f, 2.0f);
	__registry.emplace<RigidBody>(e);
	__registry.emplace<LinearCameraFollow>(e, __camera, 1.0f);
	auto& mat = __registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png", TextureType::Single));
	__registry.emplace<Player>(e);
	__registry.emplace<RenderTag>(e, RenderType::World);
	__registry.emplace<Collider>(e, ColliderType::Box, std::make_shared<BoxCollider>(100.0f, 100.0f));
	//__registry.emplace<Collider>(e, ColliderType::Point, std::make_shared<PointCollider>());
	//__registry.emplace<Collider>(e, ColliderType::Circle, std::make_shared<CircleCollider>(100.0f));

	auto e2 = __registry.create();
	__registry.emplace<Transform>(e2, glm::vec2(600, 0.0f), glm::vec2(400, 400), 0.0f);
	auto& mat2 = __registry.emplace<Material>(e2);
	mat2.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	__registry.emplace<RenderTag>(e2, RenderType::World);
	__registry.emplace<Collider>(e2, ColliderType::Box, std::make_shared<BoxCollider>(200.0f, 200.0f));

	auto e3 = __registry.create();
	auto& tform3 = __registry.emplace<Transform>(e3, glm::vec2(-1255.0f, 695.0f), glm::vec2(50.0f, 50.0f), 0.0f, 10.0f);
	auto& mat3 = __registry.emplace<Material>(e3);
	mat3.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat3.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/x.png", TextureType::Single));
	__registry.emplace<RenderTag>(e3, RenderType::Screen);
	auto& gc = __registry.emplace<GuiContainer>(e3, __camera);
	gc.add_element(std::make_shared<ExitButton>(&__shutdown, tform3));

	auto e4 = __registry.create();
	__registry.emplace<Transform>(e4, glm::vec2(-300.0f, 0.0f), glm::vec2(200.0f, 200.0f), 45.0f);
	auto& mat4 = __registry.emplace<Material>(e4);
	mat4.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	__registry.emplace<RenderTag>(e4, RenderType::World);
	__registry.emplace<Collider>(e4, ColliderType::Circle, std::make_shared<CircleCollider>(141.421f));
}
