#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"


namespace engine {

	class Key : public Object {
		friend Keyboard;
	private:
		double timeOfLastChange = glfwGetTime();
		int lastState = GLFW_RELEASE;
		int currentState = GLFW_RELEASE;

		const int keyCode;

		Key(int keyCode) : keyCode(keyCode) {}

		void clearSignals();

		void setState(GLFWwindow *window);
		void attachedToWindow(GLFWwindow *window);

	public:

		inline bool isPressed() const { return currentState == GLFW_PRESS; }

		inline bool isReleased() const { return currentState == GLFW_RELEASE; }

		inline double getTimeOfLastChange() const { return timeOfLastChange; }

		const Signal<> onPress;
		const Signal<> onPressed;
		const Signal<> onRelease;
		const Signal<> onReleased;
	};

	class Keyboard : public Object {
		friend InputInterface;
	private:
		InputInterface* inputInterface;
		double timeOfLastState = glfwGetTime();
		double timeOfCurrentState = glfwGetTime();
		std::map<int, Key *> keys;
		void updateState();
	public:
		explicit Keyboard(InputInterface* ii);
		void clearSignals();

		Key W = GLFW_KEY_W;
		Key A = GLFW_KEY_A;
		Key S = GLFW_KEY_S;
		Key D = GLFW_KEY_D;
		Key LShift = GLFW_KEY_LEFT_SHIFT;
		Key RShift = GLFW_KEY_RIGHT_SHIFT;
		Key Space = GLFW_KEY_SPACE;
		Key Escape = GLFW_KEY_ESCAPE;

		double getTimeOfCurrentState() const;
		double getTimeOfLastState() const;
		double getDeltaTimeOfState() const;

		bool isShiftPressed() const;

		void attachedToScene(const Scene *scene);
		void unattachedFromScene(const Scene *scene);
	};
}
