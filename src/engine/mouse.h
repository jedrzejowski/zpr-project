#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"


namespace engine {
	class Mouse : public Object {
		friend InputInterface;
	private:
		glm::vec2 lastPosition;
		glm::vec2 currentPosition;
		bool inWindow = false;
		bool attachedToCenter = false;

		void updateState(GLFWwindow *window);
		glm::vec2 getPosFromGLFW(GLFWwindow *window);
		void setPosToGLFW(GLFWwindow *window, const glm::vec2 &pos);

	public:
		Mouse(Object *parent = nullptr);

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

		void attachedToScene(const Scene *pScene);
		void unattachedFromScene(const Scene *pScene);
	};
}

