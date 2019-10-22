#include "keyboard.h"

/**
 * Makro jest po to aby kod był czytelniejszy,
 * bo wsadzenie takiego kolosa byłoby kiepskie
 */
#define addKey(key) keys.insert(std::pair<int, Key*>(key.keyCode, &key))

engine::Keyboard::Keyboard() {
	addKey(W);
	addKey(A);
	addKey(S);
	addKey(D);
	addKey(LShift);
	addKey(RShift);
	addKey(Space);
}

void engine::Keyboard::loopIter(GLFWwindow *window) {
	for (auto &iter : keys)
		iter.second->setState(window);
}

void engine::Keyboard::clearSignals() {
	timeOfLastState = timeOfCurrentState;
	timeOfCurrentState = glfwGetTime();

	for (auto &iter : keys)
		iter.second->clearSignals();
}

bool engine::Keyboard::isShiftPressed() const {
	return LShift.isPressed() || RShift.isPressed();
}

void engine::Key::setState(GLFWwindow *window) {

	lastState = currentState;
	currentState = glfwGetKey(window, keyCode);

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

void engine::Key::clearSignals() {
	onPress.disconnectAll();
	onPressed.disconnectAll();
	onRelease.disconnectAll();
	onReleased.disconnectAll();
}
