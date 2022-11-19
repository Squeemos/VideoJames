#pragma once

#include <vector>
#include <memory>

class GuiElement;

class GuiContainer
{
public:
	GuiContainer() {}
	~GuiContainer() {}

	void update();
	void add_element(std::shared_ptr<GuiElement> ge);

private:
	std::vector<std::shared_ptr<GuiElement>> elements;
};

class GuiElement
{
public:
	GuiElement() {}
	virtual ~GuiElement() {}

	virtual void update() = 0;

protected:

private:
	
};

class ExitButton : public GuiElement
{
public:
	ExitButton() = delete;
	ExitButton(bool* ev) : exit_value(ev) {}
	~ExitButton() { exit_value = nullptr; }

	void update();

private:
	bool* exit_value;
};