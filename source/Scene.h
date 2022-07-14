#pragma once

#include <memory>

class Entity;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	void update(double dt);

	Camera& get_camera();

	std::unique_ptr<Entity> ent;  // This needs to be better, but will work for now

private:
	std::unique_ptr<Camera> camera;
};