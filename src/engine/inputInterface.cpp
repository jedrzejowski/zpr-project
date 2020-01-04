//
// Created by adam on 23.10.2019.
//

#include "inputInterface.h"

#include <memory>

engine::InputInterface::InputInterface() {

	mouse = MousePtr(new Mouse(this));
	keyboard = KeyboardPtr(new Keyboard(this));
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
	onUnattached();
	this->scene = SceneWPtr();
}

engine::SceneWPtr engine::InputInterface::getScene() const {
	return scene;
}
