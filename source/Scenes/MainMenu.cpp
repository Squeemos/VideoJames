#include "MainMenu.h"

#include "../Trace.h"

#include "../Systems/ResourceManager.h"
#include "../Systems/InputManager.h"
#include "../Systems/SceneManager.h"

#include "../Components/Tags.h"
#include "../Components/Player.h"
#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/LinearCameraFollow.h"
#include "../Components/Collision.h"
#include "../Components/Delegate.h"

#include <memory>

inline static void try_get_delegate(entt::entity first, entt::registry& r, SignalType signal, entt::entity second = entt::null)
{
	Delegator* delegator = r.try_get<Delegator>(first);
	if (delegator)
		delegator->invoke(signal, first, r, second);
}

inline static void check_handle_collision(entt::registry& r, entt::entity first, entt::entity second, Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform)
{
	CollisionInfo info = Collider::check_collision(first_collider, first_transform, second_collider, second_transform);
	if (info.collided)
	{
		try_get_delegate(first, r, SignalType::BeginCollide, second);
		try_get_delegate(second, r, SignalType::BeginCollide, first);
	}
	else
	{
		try_get_delegate(first, r, SignalType::ExitCollide, second);
		try_get_delegate(second, r, SignalType::ExitCollide, first);
	}
}

MainMenu::MainMenu(SceneManager* scene_manager)
{
	trace_message("Creating Main Menu");

	__camera = std::make_shared<Camera>();
	__scene_manager = scene_manager;
	__scene_name = "Main Menu";

	init();
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(double& dt)
{
	dt;
	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_R))
	{
		init();
		return;
	}

	glm::vec2 mouse_pos = InputManager::get_instance().get_mouse_position();
	glm::vec2 mouse_camera_pos = __camera->mouse_to_screen(mouse_pos);
	glm::vec2 mouse_world_pos = __camera->mouse_to_world(mouse_pos);
	__registry.view<Mouse, Transform, ScreenCollider>().each([&mouse_camera_pos](auto& tform)
		{
			tform.set_translation(mouse_camera_pos);
		}
	);

	__registry.view<Mouse, Transform, DynamicCollider>().each([&mouse_world_pos](auto& tform)
		{
			tform.set_translation(mouse_world_pos);
		}
	);

	// Do this with dynamic colliders vs all colliders
	auto dynamic_colliders = __registry.view<Transform, Collider, DynamicCollider>();
	auto static_colliders = __registry.view<Transform, Collider, StaticCollider>();

	// Iterate through all dynamic colliders
	for (auto first = dynamic_colliders.begin(); first != dynamic_colliders.end(); ++first)
	{
		auto [first_tform, first_collider] = dynamic_colliders.get(*first);

		// Iterate through all next dynamic colliders
		for (auto second = std::next(first); second != dynamic_colliders.end(); ++second)
		{
			auto [second_tform, second_collider] = dynamic_colliders.get(*second);

			// Check collision and handle
			check_handle_collision(__registry, *first, *second, first_collider, first_tform, second_collider, second_tform);
		}

		// Iterate through all static colliders
		for (auto second = static_colliders.begin(); second != static_colliders.end(); ++second)
		{
			auto [second_tform, second_collider] = static_colliders.get(*second);

			// Check collision and handle
			check_handle_collision(__registry, *first, *second, first_collider, first_tform, second_collider, second_tform);
		}
	}

	auto mouse_view = __registry.view<Mouse, Transform, Collider, ScreenCollider>();
	auto screen_objects_view = __registry.view<Transform, Collider, ScreenCollider>();

	// Iterate through all mouse objects
	for (auto [mouse, mouse_transform, mouse_collider] : mouse_view.each())
	{
		// Iterate through all screen colliders
		for (auto [screen_object, so_transform, so_collider] : screen_objects_view.each())
		{
			check_handle_collision(__registry, mouse, screen_object, mouse_collider, mouse_transform, so_collider, so_transform);
		}
	}

	auto delete_view = __registry.view<DeletedTag>();
	__registry.destroy(delete_view.begin(), delete_view.end());
}

void MainMenu::init()
{
	__registry.clear();

	auto e = __registry.create();
	__registry.emplace<Transform>(e, glm::vec2(700, 200.0f), glm::vec2(400.0f, 150.0f), 0.0f, 2.0f);
	auto& mat = __registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_color(glm::vec3(1.0f, 0.0f, 1.0f));
	__registry.emplace<RenderTag>(e, RenderType::Screen);
	__registry.emplace<Collider>(e, ColliderType::Box, std::make_shared<BoxCollider>(200.0f, 75.0f));
	__registry.emplace<ScreenCollider>(e);

	auto change_scenes = [this](entt::entity self, entt::registry& r, entt::entity other)
	{
		self;
		r;
		other;

		if(InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT))
			__scene_manager->change_scene("Sandbox");
	};


	__registry.emplace<Delegator>(e).add_delegate(SignalType::BeginCollide, change_scenes);

	auto e5 = __registry.create();
	__registry.emplace<Mouse>(e5);
	__registry.emplace<Transform>(e5);
	__registry.emplace<Collider>(e5, ColliderType::Point, std::make_shared<PointCollider>());
	__registry.emplace<ScreenCollider>(e5);
}
