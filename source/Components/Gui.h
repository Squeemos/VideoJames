#pragma once

#include <vector>
#include <memory>

class GuiElement;
class Camera;

#include "Transform.h"

class GuiContainer
{
public:
	GuiContainer() = delete;
	GuiContainer(std::shared_ptr<const Camera> cam) : camera(cam) {}
	~GuiContainer() {}

	void update();
	void add_element(std::shared_ptr<GuiElement> ge);

private:
	std::vector<std::shared_ptr<GuiElement>> elements;
	std::shared_ptr<const Camera> camera;
};

class GuiElement
{
public:
	GuiElement() {}
	virtual ~GuiElement() {}

	virtual void update() = 0;

	void add_camera(std::shared_ptr<const Camera> cam) { camera = cam; }

protected:
	std::shared_ptr<const Camera> camera;
private:
	
};

class ExitButton : public GuiElement
{
public:
	ExitButton() = delete;
	ExitButton(bool* ev, const Transform tform) : exit_value(ev), transform(tform) {}
	~ExitButton() { exit_value = nullptr; }

	void update();

private:
	bool* exit_value;
	const Transform transform;
};