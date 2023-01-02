#pragma once
#include "Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu(SceneManager* scene_manager);
	~MainMenu() override;

	void update(double& dt) override;
	void init() override;
};