#pragma once

class Shader;

#include "SceneManager.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Camera>& cam);
	~Renderer();

	void render(RenderList renderables);
	void update_camera(std::shared_ptr<Camera>& cam);

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Camera> camera;
};

