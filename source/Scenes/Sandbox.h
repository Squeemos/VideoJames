#pragma once
#include "Scene.h"
class Sandbox : public Scene
{
public:
	Sandbox();
	virtual ~Sandbox();

	virtual void update(double& dt);
};

