#pragma once

#include <vector>
#include <memory>

class GuiElement;
class Camera;

#include "Transform.h"
#include <entt/entt.hpp>

class GuiContainer
{
public:
	GuiContainer() = delete;
	GuiContainer(std::shared_ptr<const Camera> cam) : __camera(cam) {}
	~GuiContainer() {}

	void update();
	void add_element(std::shared_ptr<GuiElement> ge);

private:
	std::vector<std::shared_ptr<GuiElement>> __elements;
	std::shared_ptr<const Camera> __camera;
};

class GuiElement
{
public:
	GuiElement() {}
	virtual ~GuiElement() {}

	virtual void update() = 0;

	void add_camera(std::shared_ptr<const Camera> cam) { __camera = cam; }

protected:
	std::shared_ptr<const Camera> __camera;
private:
	
};