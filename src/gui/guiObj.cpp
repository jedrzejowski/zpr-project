#include "guiObj.h"
#include "interface.h"

gui::GuiObject::GuiObject(Interface *parent) :
		Object(parent) {
}

const glm::vec3 &gui::GuiObject::getPosition() const {
	return position;
}

void gui::GuiObject::setPosition(const glm::vec3 &postion) {
	GuiObject::position = postion;
}
