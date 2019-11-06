#include "guiObj.h"
#include "interface.h"

gui::GuiObject::GuiObject(Interface *interface) :
		Object(interface),
		Sub3DObj(interface),
		interface(interface) {
}

gui::GuiObject::GuiObject(GuiObject *parent) :
		Object(parent),
		Sub3DObj(parent),
		guiParent(parent),
		interface(parent->getInterface()) {
}

const glm::mat4 &gui::GuiObject::getModel() const {
	return model;
}

void gui::GuiObject::setModel(const glm::mat4 &model) {
	GuiObject::model = model;
	setNeedRefreshBuffers(true);
}

const gui::Interface* gui::GuiObject::getInterface() const {
	return interface;
}

gui::Interface *gui::GuiObject::getInterface() {
	return interface;
}
