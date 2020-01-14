/**
 * @file InputButton.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/OpenGL.h"
#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "src/lib/Signal.hpp"

namespace engine {

	/**
	 * @brief Baza dla implementacja przycisku od myszki i klawiatury
	 */
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

		/**
		 * @brief Sygnał, który jest wywoływany co pętle mówiący, że przycisk jest wciśnięty
		 */
		const Signal<> onPress;

		/**
		 * @brief Sygnał, który jest wywoływany gdy przycisk zmienił swój stan na wciśnięty
		 */
		const Signal<> onPressed;

		/**
		 * @brief Sygnał, który jest wywoływany co pętle mówiący, że przycisk jest wyciśnięty
		 */
		const Signal<> onRelease;

		/**
		 * @brief Sygnał, który jest wywoływany gdy przycisk zmienił swój stan na wyciśnięty
		 */
		const Signal<> onReleased;

		const int& getBtnCode() const;

	};
}
