#pragma once

#include <entt/entt.hpp>

#include <unordered_map>
#include <string>
#include <memory>

#include "../Components/Transform.h"
#include "../Components/Material.h"

typedef entt::basic_view<entt::type_list<entt::constness_as_t<entt::storage_type_t<Transform, entt::entity>, Transform>, entt::constness_as_t<entt::storage_type_t<Material, entt::entity>, Material>>, entt::type_list<>, void> RenderList;

class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double& dt);
	void change_scene(const std::string& scene_name);

	RenderList get_renderables();

	std::shared_ptr<Camera>& get_camera() const;

	bool scene_changed() const;

private:
	class Scene
	{
		friend SceneManager;
	public:
		Scene();
		~Scene();
		Scene(const std::string& name);

		void update(double& dt);
	private:
		entt::registry registry;
		std::string scene_name;
		std::shared_ptr<Camera> camera;
	};

	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> current_scene;

	bool changing_scene;
};

