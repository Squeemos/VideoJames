#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>

class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	virtual void update(double dt, glm::vec2& mouse) = 0;
	virtual void draw() = 0;

	Camera& get_camera();

protected:
	std::unique_ptr<Camera> camera;
	entt::registry registry;
	std::unordered_map<std::string, entt::entity> entities_with_names; // Useful to find entities with a certain name a lot faster than using entt's view/group

private:
};