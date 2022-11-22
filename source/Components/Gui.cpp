#include "Gui.h"
#include "../Systems/InputManager.h"
#include "../Systems/Camera.h"

#include "../Trace.h"

#include <string>

void GuiContainer::update()
{
	for (std::shared_ptr<GuiElement> ge : elements)
		ge->update();
} 

void GuiContainer::add_element(std::shared_ptr<GuiElement> ge)
{
	ge->add_camera(camera);
	elements.push_back(ge);
}

void ExitButton::update()
{
	glm::vec2 mouse_pos = camera->mouse_to_screen(InputManager::get_instance().get_mouse_position());
	glm::vec2 transform_pos = transform.get_translation();
	glm::vec2 transform_scale = transform.get_scale();
	if (InputManager::get_instance().check_mouse_clicked(GLFW_MOUSE_BUTTON_LEFT))
	{
		bool left = mouse_pos.x >= (transform_pos.x - (transform_scale.x / 2));
		bool right = mouse_pos.x <= (transform_pos.x + (transform_scale.x / 2));
		bool top = mouse_pos.y <= (transform_pos.y + (transform_scale.y / 2));
		bool bot = mouse_pos.y >= (transform_pos.y - (transform_scale.y / 2));
		if(left && right && top && bot)
			*exit_value = true;
	}
}