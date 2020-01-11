/**
 * @file Mouse.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Mouse.h"
#include "Window.h"
#include "InputInterface.h"

engine::Mouse::Mouse(engine::InputInterface *ii) :
		InputDevice(ii) {
	logger(4).constructor(this);

	addBtn(Left);
	addBtn(Right);
	addBtn(Middle);
}

void engine::Mouse::initState(GLFWwindow *window) {
	last_position = current_position = getGlfwPosition(window);

	if (isAttachedToCenter()) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);;

		setGlfwPosition(window, glm::vec2(width / 2, height / 2));
	}

	InputDevice::initState(window);
}

void engine::Mouse::updateState(GLFWwindow *window) {

	last_position = current_position;
	current_position = getGlfwPosition(window);

	{
		bool was = is_in_window;
		is_in_window = glfwGetWindowAttrib(window, GLFW_FOCUSED);

		if (was != is_in_window) {
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
	return is_in_window;
}

bool engine::Mouse::isAttachedToCenter() const {
	return attached_to_center;
}

void engine::Mouse::setAttachedToCenter(bool attachedToCenter) {
	Mouse::attached_to_center = attachedToCenter;
}

const glm::vec2 &engine::Mouse::getLastPosition() const {
	return last_position;
}

const glm::vec2 &engine::Mouse::getCurrentPosition() const {
	return current_position;
}

glm::vec2 engine::Mouse::getDeltaX() const {
	return last_position - current_position;
}

glm::vec2 engine::Mouse::getDeltaY() const {
	return last_position - current_position;
}

glm::vec2 engine::Mouse::getGlfwPosition(GLFWwindow *window) {
	double tx, ty;
	glfwGetCursorPos(window, &tx, &ty);
	return glm::vec2(tx, ty);
}

void engine::Mouse::setGlfwPosition(GLFWwindow *window, const glm::vec2 &pos) {

	glfwSetCursorPos(window, pos.x, pos.y);

	last_position = current_position = pos;
}

engine::Mouse::~Mouse() {
	logger(4).destructor(this);
}


int engine::MouseBtn::getGlfwState(GLFWwindow *window) {
	return glfwGetMouseButton(window, getBtnCode());
}
