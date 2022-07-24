#pragma once
#include "Scene.h"

class SandboxScene : public Scene
{
public:
	SandboxScene();
	~SandboxScene();
	void update(double dt, glm::vec2& mouse);
	void draw();
};

