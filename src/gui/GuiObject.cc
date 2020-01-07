/**
 * @file GuiObject.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "GuiObject.h"
#include "Interface.h"

gui::GuiObject::GuiObject(gui::InterfacePtr interface) :
		Sub3DObj(interface),
		interface(interface) {
}


gui::GuiObject::GuiObject(GuiObjectPtr parent) :
		Sub3DObj(parent),
		guiParent(parent),
		interface(parent->getInterface()) {
}

glm::mat4 gui::GuiObject::getModel() const {
	if (!guiParent.expired())
		return guiParent.lock()->getModel() * model;

	return model;
}

void gui::GuiObject::setModel(const glm::mat4 &model) {
	GuiObject::model = model;
	setNeedRefreshBuffers(true);
}

const gui::InterfacePtr gui::GuiObject::getInterface() const {
	return interface.lock();
}

gui::InterfacePtr gui::GuiObject::getInterface() {
	return interface.lock();
}

gui::GuiObjectPtr gui::GuiObject::getGuiParent() const {
	return guiParent.lock();
}