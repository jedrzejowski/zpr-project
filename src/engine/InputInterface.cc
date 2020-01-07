/**
 * @file InputInterface.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InputInterface.h"

#include <memory>

engine::InputInterface::InputInterface() {
	logger.constructor(this);

	mouse = MousePtr(new Mouse(this));
	keyboard = KeyboardPtr(new Keyboard(this));
}

engine::InputInterface::~InputInterface() {
	logger.destructor(this);
}

engine::MousePtr engine::InputInterface::getMouse() {
	return mouse;
}

engine::KeyboardPtr engine::InputInterface::getKeyboard() {
	return keyboard;
}

void engine::InputInterface::initState(GLFWwindow *window) {
	keyboard->initState(window);
	mouse->initState(window);
}

void engine::InputInterface::updateState(GLFWwindow *window) {
	keyboard->updateState(window);
	mouse->updateState(window);
}

bool engine::InputInterface::isAttachedToScene() {
	return !scene.expired();
}

void engine::InputInterface::attachToScene(SceneWPtr scene) {
	this->scene = scene;
	onAttached();
}

void engine::InputInterface::unattachFromScene() {
	logger.log("odpinanie od sceny").log(this);
	onUnattached();
	logger.log("odpinanie od sceny2");
	this->scene = SceneWPtr();
	logger.log("odpinanie od sceny3");
}

engine::SceneWPtr engine::InputInterface::getScene() const {
	return scene;
}
