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
	addBtn(Num0);
	addBtn(Num1);
	addBtn(Num2);
	addBtn(Num3);
	addBtn(Num4);
	addBtn(Num5);
	addBtn(Num6);
	addBtn(Num7);
	addBtn(Num8);
	addBtn(Num9);
}

bool engine::Keyboard::isShiftPressed() const {
	return LShift.isPressed() || RShift.isPressed();
}

int engine::KeyboardBtn::getGlfwState(GLFWwindow *window) {
	return glfwGetKey(window, getBtnCode());
}
