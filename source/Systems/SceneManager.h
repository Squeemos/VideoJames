#pragma once

#include <unordered_map>
#include <string>
#include <memory>

// Include the base class
#include "../Scenes/Scene.h"

// Rendering components
#include "../Components/Transform.h"
#include "../Components/Material.h"

// A really ugly typedef so we can return a view of the current scene's registry of renderables
typedef entt::basic_view<
	entt::type_list<
		entt::constness_as_t<entt::storage_type_t<Transform, entt::entity>, Transform>, 
		entt::constness_as_t<entt::storage_type_t<Material, entt::entity>, Material>>,
	entt::type_list<>, 
	void> RenderList;

// The manager of the things on the screen
class SceneManager
{
public:
	// Start everything or clean it up
	SceneManager();
	~SceneManager();

	// This will interact with the current scene and update the state if any changes happen
	void update(double& dt);
	void change_scene(const std::string& scene_name);
	void add_scene(const std::shared_ptr<Scene>& scene);

	// Get the list of renderables in the current scene
	RenderList get_renderables() const;

	// A way to give the renderer the current scene's camera
	std::shared_ptr<Camera>& get_camera() const;

	// To let the engine know if we need to update anything since the scene changed
	bool scene_changed() const;

private:
	// A map of the scenes that are loaded
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;

	// The current scene to be processed and rendered
	std::shared_ptr<Scene> current_scene;

	// Whether or now the scene is changing so we can tell the engine
	bool changing_scene;
};

