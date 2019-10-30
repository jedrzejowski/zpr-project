#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "inputButton.h"

namespace engine {

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

