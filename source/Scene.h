#pragma once

#include <memory>
#include <vector>

class Entity;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	virtual void update(double dt);
	virtual void draw();

	void set_camera(std::unique_ptr<Camera> cam);
	Camera& get_camera();

protected:
	std::vector<std::unique_ptr<Entity>> entity_list;
	std::unique_ptr<Camera> camera;

private:
};