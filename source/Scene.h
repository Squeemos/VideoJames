#pragma once

#include <memory>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

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

private:
};