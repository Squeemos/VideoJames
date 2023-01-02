#pragma once
#include "Scene.h"

// Sandbox scene for testing
class Sandbox : public Scene
{
public:
	Sandbox(SceneManager* scene_manager);
	~Sandbox() override;

	void update(double& dt) override;
	void init() override;
};

