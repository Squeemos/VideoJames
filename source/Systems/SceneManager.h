#pragma once

#include <unordered_map>
#include <string>
#include <memory>

// Include the base class
#include "../Scenes/Scene.h"

// Rendering components
#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "../Components/RenderTag.h"

// Typedef for a list of objects to render, this way we only need to edit it in one place
typedef entt::view<entt::get_t<const Transform, const Material, const RenderTag>> RenderList;

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

	bool finished() const;
	bool shutdown() const;

private:
	// A map of the scenes that are loaded
	std::unordered_map<std::string, std::shared_ptr<Scene>> __scenes;

	// The current scene to be processed and rendered
	std::shared_ptr<Scene> __current_scene;

	// Whether or now the scene is changing so we can tell the engine
	bool __changing_scene;
};

