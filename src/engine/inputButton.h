#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"

namespace engine {
	class InputButton : public Object {
		friend InputDevice;
	private:
		double timeOfLastChange = glfwGetTime();
		int lastState = GLFW_RELEASE;
		int currentState = GLFW_RELEASE;

		const int btnCode;

	protected:
		void initState(GLFWwindow *window);
		void updateState(GLFWwindow *window);

		virtual int getGlfwState(GLFWwindow *window) = 0;

		explicit InputButton(int btnCode) : btnCode(btnCode) {}
	public:

		void clearSignals();

		inline bool isPressed() const { return currentState == GLFW_PRESS; }

		inline bool isReleased() const { return currentState == GLFW_RELEASE; }

		inline double getTimeOfLastChange() const { return timeOfLastChange; }

		const Signal<> onPress;
		const Signal<> onPressed;
		const Signal<> onRelease;
		const Signal<> onReleased;

		const int getBtnCode() const;
	};
}
