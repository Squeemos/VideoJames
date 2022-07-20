#pragma once

#include <memory>
#include <entt/entt.hpp>

class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	virtual void update(double dt) = 0;
	virtual void draw() = 0;

	Camera& get_camera();

protected:
	std::unique_ptr<Camera> camera;
	entt::registry registry;

private:
};