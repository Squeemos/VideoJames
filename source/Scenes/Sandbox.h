#pragma once
#include "Scene.h"

// Sandbox scene for testing
class Sandbox : public Scene
{
public:
	Sandbox();
	virtual ~Sandbox();

	void update(double& dt);
	void init();
};

