//
// Created by adam on 22.10.2019.
//

#include "mouse.h"
#include "window.h"

engine::Mouse::Mouse(engine::Window *window) : Object(window) {
}

void engine::Mouse::updateState(GLFWwindow *window) {
	lastX = curX;
	lastY = curY;
	glfwGetCursorPos(window, &curX, &curY);

	{
		bool was = inWindow;
		inWindow = glfwGetWindowAttrib(window, GLFW_HOVERED);

		if (was != inWindow) {
			if (was) onLeave.emit();
			else onEnter.emit();
		}
	}

	if (isInWindow()) {
		auto dx = getDeltaX(), dy = getDeltaY();

		if (dx != 0 || dy != 0)
			onMove.emit(dx, dy);
	}

	if (isAttachedToCenter()) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);;

		double sceneXCenter = width / 2,
				sceneYCenter = height / 2;

		glfwSetCursorPos(window, sceneXCenter, sceneYCenter);

		lastX = curX;
		lastY = curY;
		curX = sceneXCenter;
		curY = sceneYCenter;
	}
}

double engine::Mouse::getCurX() const {
	return curX;
}

double engine::Mouse::getCurY() const {
	return curY;
}

double engine::Mouse::getLastX() const {
	return lastX;
}

double engine::Mouse::getLastY() const {
	return lastY;
}

double engine::Mouse::getDeltaX() const {
	return lastX - curX;
}

double engine::Mouse::getDeltaY() const {
	return lastY - curY;
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

