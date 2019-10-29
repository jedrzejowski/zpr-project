#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"
#include "inputDevice.h"


namespace engine {
	class Mouse : public InputDevice {
		friend InputInterface;
	private:
		glm::vec2 lastPosition;
		glm::vec2 currentPosition;
		bool inWindow = false;
		bool attachedToCenter = false;


		glm::vec2 getGlfwPosition(GLFWwindow *window);
		void setGlfwPosition(GLFWwindow *window, const glm::vec2 &pos);

	protected:
		void initState(GLFWwindow *window) override;
		void updateState(GLFWwindow *window) override;

	public:
		explicit Mouse(InputInterface *ii);

		const Signal<const glm::vec2 &> onMove;
		const Signal<> onLeave;
		const Signal<> onEnter;

		const glm::vec2 &getLastPosition() const;
		const glm::vec2 &getCurrentPosition() const;
		glm::vec2 getDeltaX() const;
		glm::vec2 getDeltaY() const;

		bool isInWindow() const;

		bool isAttachedToCenter() const;
		void setAttachedToCenter(bool attachedToCenter);
	};
}

