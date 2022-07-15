#pragma once
#include "Scene.h"

#include <memory>
#include <vector>

class Entity;

class SandboxScene : public Scene
{
public:
	SandboxScene();
	~SandboxScene();
	void update(double dt);
	void draw();
};

