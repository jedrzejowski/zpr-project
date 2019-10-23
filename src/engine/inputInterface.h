#include "src/_classdef.h"
#include "src/lib/object.h"
#include "mouse.h"
#include "keyboard.h"

namespace engine {
	class InputInterface : public Object {
		friend Window;
	private:
		Mouse mouse;
		Keyboard keyboard;

		void updateState(GLFWwindow *window);
	public:
		InputInterface();

		const Signal<Window *> onAttached;
		const Signal<Window *> onUnattached;

		Mouse &getMouse();
		Keyboard &getKeyboard();
	};
}
