#pragma once

#include <entt/entt.hpp>

#include <unordered_map>
#include <string>
#include <memory>

class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double& dt);

	const entt::registry& get_renderables() const;
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

