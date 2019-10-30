#include "keyboard.h"
#include "window.h"
#include "inputInterface.h"

engine::Keyboard::Keyboard(InputInterface *ii) :
		InputDevice(ii) {

	addBtn(W);
	addBtn(A);
	addBtn(S);
	addBtn(D);
	addBtn(LShift);
	addBtn(RShift);
	addBtn(Space);
	addBtn(Escape);
}

bool engine::Keyboard::isShiftPressed() const {
	return LShift.isPressed() || RShift.isPressed();
}

int engine::KeyboardBtn::getGlfwState(GLFWwindow *window) {
	return glfwGetKey(window, getBtnCode());
}
