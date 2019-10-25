//
// Created by adam on 23.10.2019.
//

#include "inputInterface.h"

engine::InputInterface::InputInterface(Object *parent) :
		Object(parent) {
}

engine::Mouse &engine::InputInterface::getMouse() {
	return mouse;
}

engine::Keyboard &engine::InputInterface::getKeyboard() {
	return keyboard;
}

void engine::InputInterface::updateState(GLFWwindow *window) {
	keyboard.updateState(window);
	mouse.updateState(window);
}
