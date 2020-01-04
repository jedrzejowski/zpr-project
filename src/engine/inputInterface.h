#include "src/_classdef.h"
#include "src/lib/object.h"
#include "mouse.h"
#include "keyboard.h"

namespace engine {
	class InputInterface : public Object {
		friend Window;
	private:
		SceneWPtr scene;
		MousePtr mouse;
		KeyboardPtr keyboard;

		void initState(GLFWwindow *window);
		void updateState(GLFWwindow *window);

	public:
		explicit InputInterface();
		~InputInterface() override;

		const Signal<> onAttached;
		const Signal<> onUnattached;

		MousePtr getMouse();
		KeyboardPtr getKeyboard();

		bool isAttachedToScene();
		void attachToScene(SceneWPtr scene);
		void unattachFromScene();
		SceneWPtr getScene() const;

	};
}
