//
// Created by adam on 23.10.2019.
//

#include "inputInterface.h"

engine::InputInterface::InputInterface(Object *parent) :
		Object(parent) {

	mouse = new Mouse(this);
	keyboard = new Keyboard(this);
}

engine::Mouse *engine::InputInterface::getMouse() {
	return mouse;
}

engine::Keyboard *engine::InputInterface::getKeyboard() {
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
	return scene == nullptr;
}

void engine::InputInterface::attachToScene(const Scene *scene) {
	this->scene = scene;
	onAttached.emit();
}

void engine::InputInterface::unattachFromScene() {
	onUnattached();
	this->scene = nullptr;
}

const engine::Scene *engine::InputInterface::getScene() const {
	return scene;
}
