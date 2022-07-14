#pragma once

#include <memory>
#include <vector>
#include <utility>

class Entity;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	virtual void update(double dt);
	virtual std::pair<std::vector<std::unique_ptr<Entity>>::iterator, std::vector<std::unique_ptr<Entity>>::iterator> draw();

	void set_camera(std::unique_ptr<Camera> cam);
	Camera& get_camera();

protected:
	std::vector<std::unique_ptr<Entity>> entity_list;

private:
	std::unique_ptr<Camera> camera;
};