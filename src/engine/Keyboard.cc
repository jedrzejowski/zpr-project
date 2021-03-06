/**
 * @file Keyboard.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Keyboard.h"
#include "Window.h"
#include "InputInterface.h"

engine::Keyboard::Keyboard(InputInterface *ii) :
		InputDevice(ii) {

	addBtn(Q);
	addBtn(W);
	addBtn(E);
	addBtn(R);

	addBtn(A);
	addBtn(S);
	addBtn(D);
	addBtn(F);

	addBtn(Z);
	addBtn(X);
	addBtn(C);
	addBtn(V);

	addBtn(LShift);
	addBtn(RShift);
	addBtn(Space);
	addBtn(Escape);

	addBtn(Tilde);
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
