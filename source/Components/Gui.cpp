#include "Gui.h"

#include "Tags.h"

#include "../Systems/InputManager.h"
#include "../Systems/Camera.h"

#include "../Trace.h"

#include <string>

void GuiContainer::update()
{
	for (std::shared_ptr<GuiElement> ge : __elements)
		ge->update();
} 

void GuiContainer::add_element(std::shared_ptr<GuiElement> ge)
{
	ge->add_camera(__camera);
	__elements.push_back(ge);
}