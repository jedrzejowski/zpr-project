#include "src/_classdef.h"
#include "src/lib/object.h"
#include "mouse.h"
#include "keyboard.h"

namespace engine {
	class InputInterface : public Object {
		friend Window;
	private:
		const Scene* scene = nullptr;
		MousePtr mouse;
		KeyboardPtr keyboard;

		void initState(GLFWwindow *window);
		void updateState(GLFWwindow *window);

	public:
		explicit InputInterface(Object* parent = nullptr);

		const Signal<> onAttached;
		const Signal<> onUnattached;

		MousePtr getMouse();
		KeyboardPtr getKeyboard();

		bool isAttachedToScene();
		void attachToScene(const Scene* scene);
		void unattachFromScene();
		const Scene *getScene() const;

	};
}
