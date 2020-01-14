/**
 * @file InputInterface.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "Mouse.h"
#include "Keyboard.h"

namespace engine {

	/**
	 * @brief Interfejs wejścia
	 *
	 * Gromadzi wejście myszki i klawiatury, interfejsów może być wiele, ale tylko jeden dostaje powiadomienia od okna
	 */
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
