#pragma once

#include <vector>
#include <memory>

class Scene;
class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double dt);
	void draw();

	void add_scene(std::shared_ptr<Scene> scene);

private:
	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> current_scene;
};