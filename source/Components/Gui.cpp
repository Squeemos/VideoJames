#include "Gui.h"
#include "../Systems/InputManager.h"

#include "../Trace.h"

#include <string>

void GuiContainer::update()
{
	for (std::shared_ptr<GuiElement> ge : elements)
		ge->update();
}

void GuiContainer::add_element(std::shared_ptr<GuiElement> ge)
{
	elements.push_back(ge);
}

void ExitButton::update()
{
	glm::vec2 mouse_pos = InputManager::get_instance().get_mouse_position();
	trace_message(std::to_string(mouse_pos.x) + " " + std::to_string(mouse_pos.y));
	if (InputManager::get_instance().check_key_pressed(GLFW_KEY_ESCAPE))
		*exit_value = true;
}