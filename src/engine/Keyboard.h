#pragma once

#include "src/OpenGL.h"
#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "InputDevice.h"
#include "InputButton.h"


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

		KeyboardBtn Num0 = GLFW_KEY_0;
		KeyboardBtn Num1 = GLFW_KEY_1;
		KeyboardBtn Num2 = GLFW_KEY_2;
		KeyboardBtn Num3 = GLFW_KEY_3;
		KeyboardBtn Num4 = GLFW_KEY_4;
		KeyboardBtn Num5 = GLFW_KEY_5;
		KeyboardBtn Num6 = GLFW_KEY_6;
		KeyboardBtn Num7 = GLFW_KEY_7;
		KeyboardBtn Num8 = GLFW_KEY_8;
		KeyboardBtn Num9 = GLFW_KEY_9;

		bool isShiftPressed() const;
	};
}
