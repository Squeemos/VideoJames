#pragma once

#include <entt/entt.hpp>

#include <unordered_map>
#include <string>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double& dt);

	const auto& get_renderables() const;

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
	};

	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> current_scene;
};

