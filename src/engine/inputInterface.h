#include "src/_classdef.h"
#include "src/lib/object.h"
#include "mouse.h"
#include "keyboard.h"

namespace engine {
	class InputInterface : public Object {
		friend Window;
	private:
		const Scene* scene = nullptr;
		Mouse mouse;
		Keyboard keyboard;

		void updateState(GLFWwindow *window);

	public:
		explicit InputInterface(Object* parent = nullptr);

		const Signal<Window *> onAttached;
		const Signal<Window *> onUnattached;

		Mouse &getMouse();
		Keyboard &getKeyboard();

		bool isAttachedToScene();
		void unattachedFromScene(const Scene* scene);
		void attachedToScene(const Scene* scene);
		const Scene *getScene() const;
	};
}
