#include <GLFW/glfw3.h>
#include "src/_classdef.h"
#include "src/lib/object.h"


namespace engine {

	class Key : public Object {
		friend Keyboard;
	private:
		int lastState = GLFW_RELEASE;
		int currentState = GLFW_RELEASE;

		const int keyCode;

		Key(int keyCode) : keyCode(keyCode) {}

		void clearSignals();

		void setState(GLFWwindow *window);

	public:

		inline bool isPressed() const {
			return currentState == GLFW_PRESS;
		}

		inline bool isReleased() const {
			return currentState == GLFW_RELEASE;
		}

		const Signal<> onPress;
		const Signal<> onPressed;
		const Signal<> onRelease;
		const Signal<> onReleased;
	};

	class Keyboard : public Object {
		friend Window;
	protected:
		std::map<int, Key *> keys;
		void loopIter(GLFWwindow *window);
	public:
		Keyboard();
		void clearSignals();

		Key W = GLFW_KEY_W;
		Key A = GLFW_KEY_A;
		Key S = GLFW_KEY_S;
		Key D = GLFW_KEY_D;
		Key LShift = GLFW_KEY_LEFT_SHIFT;
		Key RShift = GLFW_KEY_RIGHT_SHIFT;
		Key Space = GLFW_KEY_SPACE;
	};
}
