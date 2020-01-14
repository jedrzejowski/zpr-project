/**
 * @file InputDevice.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/OpenGL.h"
#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "InputButton.h"

namespace engine {

	/**
	 * @brief Implementacja urządzenia wejścia
	 */
	class InputDevice : public Object {
		friend InputInterface;
	private:
		double timeOfLastState = glfwGetTime();
		double timeOfCurrentState = glfwGetTime();

		InputInterface *inputInterface;

		std::map<int, InputButton *> inputButtons;

	protected:

		virtual void updateState(GLFWwindow *window);
		virtual void initState(GLFWwindow *window);

		void addBtn(InputButton &btn);

	public:
		explicit InputDevice(InputInterface *ii);

		double getTimeOfCurrentState() const;
		double getTimeOfLastState() const;
		double getDeltaTimeOfState() const;

		const Signal<> onStateChange;
	};
}

