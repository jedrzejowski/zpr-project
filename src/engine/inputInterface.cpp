//
// Created by adam on 23.10.2019.
//

#include "inputInterface.h"

engine::InputInterface::InputInterface(Object *parent) :
		Object(parent),
		mouse(this),
		keyboard(this) {
}

engine::Mouse &engine::InputInterface::getMouse() {
	return mouse;
}

engine::Keyboard &engine::InputInterface::getKeyboard() {
	return keyboard;
}

void engine::InputInterface::updateState(GLFWwindow *window) {
	keyboard.updateState(window);
	mouse.updateState();
}

bool engine::InputInterface::isAttachedToScene() {
	return scene == nullptr;
}

void engine::InputInterface::attachedToScene(const Scene *scene) {
	this->scene = scene;
	keyboard.attachedToScene(scene);
	mouse.attachedToScene(scene);
}

void engine::InputInterface::unattachedFromScene(const engine::Scene *scene) {
	keyboard.unattachedFromScene(scene);
	mouse.unattachedFromScene(scene);
	this->scene = nullptr;
}

const engine::Scene *engine::InputInterface::getScene() const {
	return scene;
}
