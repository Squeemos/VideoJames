#pragma once

#include <unordered_map>
#include <string>
#include <memory>

// Include the base class
#include "../Scenes/Scene.h"

// Rendering components
#include "../Components/Transform.h"
#include "../Components/Material.h"

typedef entt::basic_view<
	entt::type_list<
		entt::constness_as_t<entt::storage_type_t<Transform, entt::entity>, Transform>, 
		entt::constness_as_t<entt::storage_type_t<Material, entt::entity>, Material>>,
	entt::type_list<>, 
	void> RenderList;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double& dt);
	void change_scene(const std::string& scene_name);
	void add_scene(const std::shared_ptr<Scene>& scene);

	RenderList get_renderables();

	std::shared_ptr<Camera>& get_camera() const;

	bool scene_changed() const;

private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> current_scene;

	bool changing_scene;
};

