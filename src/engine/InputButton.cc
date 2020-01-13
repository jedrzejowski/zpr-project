/**
 * @file InputButton.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InputButton.h"

void engine::InputButton::updateState(GLFWwindow *window) {

	last_state = current_state;
	current_state = getGlfwState(window);

	if (current_state == GLFW_RELEASE) {
		if (last_state == GLFW_PRESS) {
			onReleased.emit();
			time_of_last_change = glfwGetTime();
		}
		onRelease.emit();
	} else {//GLFW_PRESS
		if (last_state == GLFW_RELEASE) {
			onPressed.emit();
			time_of_last_change = glfwGetTime();
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
	current_state = last_state = glfwGetKey(window, btnCode);
}

const int& engine::InputButton::getBtnCode() const {
	return btnCode;
}
