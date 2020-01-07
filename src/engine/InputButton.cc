/**
 * @file InputButton.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InputButton.h"

void engine::InputButton::updateState(GLFWwindow *window) {

	lastState = currentState;
	currentState = getGlfwState(window);

	if (currentState == GLFW_RELEASE) {
		if (lastState == GLFW_PRESS) {
			onReleased.emit();
			timeOfLastChange = glfwGetTime();
		}
		onRelease.emit();
	} else {//GLFW_PRESS
		if (lastState == GLFW_RELEASE) {
			onPressed.emit();
			timeOfLastChange = glfwGetTime();
		}
		onPress.emit();
	}
}

void engine::InputButton::clearSignals() {
	onPress.disconnectAll();
	onPressed.disconnectAll();
	onRelease.disconnectAll();
	onReleased.disconnectAll();
}

void engine::InputButton::initState(GLFWwindow *window) {
	currentState = lastState = glfwGetKey(window, btnCode);
}

const int engine::InputButton::getBtnCode() const {
	return btnCode;
}
