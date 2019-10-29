#include "keyboard.h"
#include "window.h"
#include "inputInterface.h"

/**
 * Makro jest po to aby kod był czytelniejszy,
 * bo wsadzenie takiego kolosa byłoby kiepskie
 */
#define addKey(key) keys.insert(std::pair<int, Key*>(key.keyCode, &key))

engine::Keyboard::Keyboard(InputInterface *ii) :
		Object(ii),
		inputInterface(ii) {

	addKey(W);
	addKey(A);
	addKey(S);
	addKey(D);
	addKey(LShift);
	addKey(RShift);
	addKey(Space);
	addKey(Escape);
}

void engine::Keyboard::updateState() {
	timeOfLastState = timeOfCurrentState;
	timeOfCurrentState = glfwGetTime();

	for (auto &iter : keys)
		iter.second->setState(window);
}

void engine::Keyboard::clearSignals() {

	for (auto &iter : keys)
		iter.second->clearSignals();
}

bool engine::Keyboard::isShiftPressed() const {
	return LShift.isPressed() || RShift.isPressed();
}

double engine::Keyboard::getTimeOfCurrentState() const { return timeOfCurrentState; }

double engine::Keyboard::getTimeOfLastState() const { return timeOfLastState; }

double engine::Keyboard::getDeltaTimeOfState() const {
	return timeOfCurrentState - timeOfLastState;
}

void engine::Keyboard::attachedToScene(const engine::Scene *scene) {
	auto window = scene->getWindow();
	if (window == nullptr) return;
	auto glfwWindow = window->getGlfwWindow();
	if (glfwWindow == nullptr) return;

	for (auto &iter : keys)
		iter.second->attachedToWindow(glfwWindow);
}

void engine::Keyboard::unattachedFromScene(const engine::Scene *scene) {
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

void engine::Key::attachedToWindow(GLFWwindow *window) {
	currentState = lastState = glfwGetKey(window, keyCode);
}
