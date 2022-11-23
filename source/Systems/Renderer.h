#pragma once

#include "SceneManager.h"

class Shader;

// A renderer that uses it's shader and the current camera to draw things
class Renderer
{
public:
	Renderer();
	~Renderer();

	// Given a list of renderables, draw them
	void render(RenderList renderables, std::shared_ptr<Camera> camera);

private:
	std::shared_ptr<Shader> __shader;
};

