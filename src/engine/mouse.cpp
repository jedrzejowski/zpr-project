//
// Created by adam on 22.10.2019.
//

#include "mouse.h"
#include "window.h"
#include "inputInterface.h"

engine::Mouse::Mouse(engine::InputInterface *ii) :
		InputDevice(ii) {

	addBtn(Left);
	addBtn(Right);
	addBtn(Middle);
}

void engine::Mouse::initState(GLFWwindow *window) {
	lastPosition = currentPosition = getGlfwPosition(window);

	if (isAttachedToCenter()) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);;

		setGlfwPosition(window, glm::vec2(width / 2, height / 2));
	}

	InputDevice::initState(window);
}

void engine::Mouse::updateState(GLFWwindow *window) {

	lastPosition = currentPosition;
	currentPosition = getGlfwPosition(window);

	{
		bool was = inWindow;
		inWindow = glfwGetWindowAttrib(window, GLFW_FOCUSED);

		if (was != inWindow) {
			if (was) onLeave.emit();
			else onEnter.emit();
		}
	}

	if (isInWindow()) {
		auto delta = getDeltaY();

		if (delta != glm::vec2(0.f, 0.f))
			onMove.emit(delta);
	}

	if (isAttachedToCenter()) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);;

		setGlfwPosition(window, glm::vec2(width / 2, height / 2));
	}

	InputDevice::updateState(window);
}


bool engine::Mouse::isInWindow() const {
	return inWindow;
}

bool engine::Mouse::isAttachedToCenter() const {
	return attachedToCenter;
}

void engine::Mouse::setAttachedToCenter(bool attachedToCenter) {
	Mouse::attachedToCenter = attachedToCenter;
}

const glm::vec2 &engine::Mouse::getLastPosition() const {
	return lastPosition;
}

const glm::vec2 &engine::Mouse::getCurrentPosition() const {
	return currentPosition;
}

glm::vec2 engine::Mouse::getDeltaX() const {
	return lastPosition - currentPosition;
}

glm::vec2 engine::Mouse::getDeltaY() const {
	return lastPosition - currentPosition;
}

glm::vec2 engine::Mouse::getGlfwPosition(GLFWwindow *window) {
	double tx, ty;
	glfwGetCursorPos(window, &tx, &ty);
	return glm::vec2(tx, ty);
}

void engine::Mouse::setGlfwPosition(GLFWwindow *window, const glm::vec2 &pos) {

	glfwSetCursorPos(window, pos.x, pos.y);

	lastPosition = currentPosition = pos;
}

engine::Mouse::~Mouse() {
	logger.log("~Mouse");
}


int engine::MouseBtn::getGlfwState(GLFWwindow *window) {
	return glfwGetMouseButton(window, getBtnCode());
}
