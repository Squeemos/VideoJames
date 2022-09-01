#pragma once

#include "SceneManager.h"

class Shader;

// A renderer that uses it's shader and the current camera to draw things
class Renderer
{
public:
	Renderer(std::shared_ptr<Camera>& cam);
	~Renderer();

	// Given a list of renderables, draw them
	void render(RenderList renderables);

	// A method to update the camera
	inline void update_camera(std::shared_ptr<Camera>& cam) { camera = cam; }

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Camera> camera;
};

