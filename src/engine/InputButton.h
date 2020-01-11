/**
 * @file InputButton.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/OpenGL.h"
#include "src/_classdef.h"
#include "src/lib/Object.hpp"

namespace engine {
	class InputButton : public Object {
		friend InputDevice;
	private:
		double time_of_last_change = glfwGetTime();
		int last_state = GLFW_RELEASE;
		int current_state = GLFW_RELEASE;

		const int btnCode;

	protected:
		void initState(GLFWwindow *window);
		void updateState(GLFWwindow *window);

		virtual int getGlfwState(GLFWwindow *window) = 0;

		explicit InputButton(int btnCode) : btnCode(btnCode) {}
	public:

		void clearSignals();

		inline bool isPressed() const { return current_state == GLFW_PRESS; }

		inline bool isReleased() const { return current_state == GLFW_RELEASE; }

		inline double getTimeOfLastChange() const { return time_of_last_change; }

		const Signal<> onPress;
		const Signal<> onPressed;
		const Signal<> onRelease;
		const Signal<> onReleased;

		const int getBtnCode() const;
	};
}
