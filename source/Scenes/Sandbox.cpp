#include "Sandbox.h"

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

static void change_color(entt::entity self, entt::registry& r, entt::entity other)
{
	other;
	r.get<Material>(self).add_color(glm::vec3(0.0f, 1.0f, 0.0f));
}

static void undo_change(entt::entity self, entt::registry& r, entt::entity other)
{
	other;
	r.get<Material>(self).add_color(glm::vec3(1.0f, 0.0f, 0.0f));
}

static void delete_object(entt::entity self, entt::registry& r, entt::entity other)
{
	other;
	if (InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT) && !r.all_of<DeletedTag>(self) && r.all_of<Mouse>(other))
		r.emplace<DeletedTag>(self);
}

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

Sandbox::Sandbox(SceneManager* scene_manager)
{
	trace_message("Creating Sandbox Scene");

	__camera = std::make_shared<Camera>();
	__scene_manager = scene_manager;
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

	__registry.view<Player, Transform>().each([&dt](auto& player, auto& tform)
		{
			player.update(dt, tform);
		}
	);

	__registry.view<LinearCameraFollow, Transform>().each([](auto& cf, auto& tform)
		{
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
		__registry.emplace<Collider>(e, ColliderType::Box, std::make_shared<BoxCollider>(100.0f, 100.0f));
		__registry.emplace<StaticCollider>(e);
		__registry.emplace<Delegator>(e).add_delegate(SignalType::BeginCollide, delete_object);
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

void Sandbox::init()
{
	__registry.clear();

	auto e = __registry.create();
	__registry.emplace<Transform>(e, glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f), 45.0f, 2.0f);
	__registry.emplace<LinearCameraFollow>(e, __camera, 1.0f);
	auto& mat = __registry.emplace<Material>(e);
	mat.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/rgba_tex.png", TextureType::Single));
	__registry.emplace<Player>(e);
	__registry.emplace<RenderTag>(e, RenderType::World);
	__registry.emplace<Collider>(e, ColliderType::Box, std::make_shared<BoxCollider>(100.0f, 100.0f));
	__registry.emplace<DynamicCollider>(e);

	auto e2 = __registry.create();
	__registry.emplace<Transform>(e2, glm::vec2(600, 0.0f), glm::vec2(400, 400), 18.0f);
	auto& mat2 = __registry.emplace<Material>(e2);
	mat2.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	__registry.emplace<RenderTag>(e2, RenderType::World);
	__registry.emplace<Collider>(e2, ColliderType::Box, std::make_shared<BoxCollider>(200.0f, 200.0f));
	__registry.emplace<Delegator>(e2).add_delegate(SignalType::BeginCollide, change_color).add_delegate(SignalType::ExitCollide, undo_change);
	__registry.emplace<StaticCollider>(e2);

	auto e3 = __registry.create();
	__registry.emplace<Transform>(e3, glm::vec2(-1255.0f, 695.0f), glm::vec2(50.0f, 50.0f), 0.0f, 10.0f);
	auto& mat3 = __registry.emplace<Material>(e3);
	mat3.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	mat3.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/x.png", TextureType::Single));
	__registry.emplace<RenderTag>(e3, RenderType::Screen);
	__registry.emplace<Collider>(e3, ColliderType::Box, std::make_shared<BoxCollider>(25.0f, 25.0f));
	__registry.emplace<ScreenCollider>(e3);

	auto exit_func = [this](entt::entity self, entt::registry& r, entt::entity other)
	{
		if (InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT))
			__shutdown = true;
		self;
		r;
		other;
	};
	__registry.emplace<Delegator>(e3).add_delegate(SignalType::BeginCollide, exit_func);

	auto e4 = __registry.create();
	__registry.emplace<Transform>(e4, glm::vec2(-300.0f, 0.0f), glm::vec2(200.0f, 200.0f), 45.0f);
	auto& mat4 = __registry.emplace<Material>(e4);
	mat4.add_mesh(ResourceManager::get_instance().find_or_construct_mesh("1b1"));
	// mat4.add_texture(ResourceManager::get_instance().find_or_construct_texture("./assets/real_circle.png", TextureType::Single));
	__registry.emplace<RenderTag>(e4, RenderType::World);
	__registry.emplace<Collider>(e4, ColliderType::Circle, std::make_shared<CircleCollider>(141.42f));
	__registry.emplace<StaticCollider>(e4);

	auto e5 = __registry.create();
	__registry.emplace<Mouse>(e5);
	__registry.emplace<Transform>(e5);
	__registry.emplace<Collider>(e5, ColliderType::Point, std::make_shared<PointCollider>());
	__registry.emplace<ScreenCollider>(e5);

	auto other_exit = [](entt::entity self, entt::registry& r, entt::entity other)
	{
		if (InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT))
			trace_message("Shutdown pressed");
		self;
		r;
		other;
	};

	__registry.emplace<Delegator>(e5).add_delegate(SignalType::BeginCollide, other_exit);

	auto e6 = __registry.create();
	__registry.emplace<Mouse>(e6);
	__registry.emplace<Transform>(e6);
	__registry.emplace<Collider>(e6, ColliderType::Point, std::make_shared<PointCollider>());
	__registry.emplace<DynamicCollider>(e6);
}
