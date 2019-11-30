#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "inputDevice.h"
#include "inputButton.h"


namespace engine {

	class KeyboardBtn : public InputButton {
		friend Keyboard;
		int getGlfwState(GLFWwindow *window) override;
		KeyboardBtn(int btnCode) : InputButton(btnCode) {};
	};

	class Keyboard : public InputDevice {
		friend InputInterface;
	private:
		explicit Keyboard(InputInterface *ii);
	public:

		KeyboardBtn W = GLFW_KEY_W;
		KeyboardBtn A = GLFW_KEY_A;
		KeyboardBtn S = GLFW_KEY_S;
		KeyboardBtn D = GLFW_KEY_D;
		KeyboardBtn LShift = GLFW_KEY_LEFT_SHIFT;
		KeyboardBtn RShift = GLFW_KEY_RIGHT_SHIFT;
		KeyboardBtn Space = GLFW_KEY_SPACE;
		KeyboardBtn Escape = GLFW_KEY_ESCAPE;

		bool isShiftPressed() const;
	};
}
