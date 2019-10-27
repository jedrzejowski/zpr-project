#include "guiObj.h"
#include "interface.h"

gui::GuiObject::GuiObject(Object *parent) : Object(parent) {
}


const glm::mat4 &gui::GuiObject::getModel() const {
	return model;
}

void gui::GuiObject::setModel(const glm::mat4 &model) {
	GuiObject::model = model;
}
