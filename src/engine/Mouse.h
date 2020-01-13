/**
 * @file Mouse.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/OpenGL.h"
#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "InputDevice.h"
#include "InputButton.h"


namespace engine {

	/**
	 * @brief Implementacja przycisku myszki
	 */
	class MouseBtn : public InputButton {
		friend Mouse;
		int getGlfwState(GLFWwindow *window) override;
		MouseBtn(int btnCode) : InputButton(btnCode) {};
	};

	class Mouse : public InputDevice {
		friend InputInterface;
	private:
		glm::vec2 last_position;
		glm::vec2 current_position;
		bool is_in_window = false;
		bool attached_to_center = false;

		glm::vec2 getGlfwPosition(GLFWwindow *window);
		void setGlfwPosition(GLFWwindow *window, const glm::vec2 &pos);

		explicit Mouse(InputInterface *ii);
	protected:
		void initState(GLFWwindow *window) override;
		void updateState(GLFWwindow *window) override;

	public:
		~Mouse() override;

		/**
		 * @brief Sygnał zmiany pozycji myszki
		 *
		 * argument to przesunięcie w współrzędnych 1:1
		 */
		const Signal<const glm::vec2 &> onMove;

		/**
		 * @brief Sygnał wyjścia myszki z okna
		 */
		const Signal<> onLeave;

		/**
		 * @brief Sygnał wejścia myszki z okna
		 */
		const Signal<> onEnter;

		MouseBtn Left = GLFW_MOUSE_BUTTON_LEFT;
		MouseBtn Right = GLFW_MOUSE_BUTTON_RIGHT;
		MouseBtn Middle = GLFW_MOUSE_BUTTON_MIDDLE;

		const glm::vec2 &getLastPosition() const;
		const glm::vec2 &getCurrentPosition() const;
		glm::vec2 getDeltaX() const;
		glm::vec2 getDeltaY() const;

		bool isInWindow() const;

		bool isAttachedToCenter() const;
		void setAttachedToCenter(bool attachedToCenter);
	};
}

