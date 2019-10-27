//
// Created by adam on 22.10.2019.
//

#include "mouse.h"
#include "window.h"

engine::Mouse::Mouse(Object *parent) : Object(parent) {
}

void engine::Mouse::updateState(GLFWwindow *window) {

	lastPosition = currentPosition;
	currentPosition = getPosFromGLFW(window);

	{
		bool was = inWindow;
		inWindow = glfwGetWindowAttrib(window, GLFW_HOVERED);

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

		currentPosition = glm::vec2(width / 2, height / 2);

		setPosToGLFW(window, currentPosition);
		lastPosition = currentPosition;
	}
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

void engine::Mouse::attachedToScene(const engine::Scene *scene) {
	auto window = scene->getWindow();
	if (window == nullptr) return;
	auto glfwWindow = window->getGlfwWindow();
	if (glfwWindow == nullptr) return;

	currentPosition = getPosFromGLFW(glfwWindow);
	lastPosition = currentPosition;
}

void engine::Mouse::unattachedFromScene(const engine::Scene *scene) {
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

glm::vec2 engine::Mouse::getPosFromGLFW(GLFWwindow *window) {
	double tx, ty;
	glfwGetCursorPos(window, &tx, &ty);
	return glm::vec2(tx, ty);
}

void engine::Mouse::setPosToGLFW(GLFWwindow *window, const glm::vec2 &pos) {
	glfwSetCursorPos(window, pos.x, pos.y);
}
