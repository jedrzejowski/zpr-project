#pragma once

#include "src/opengl.h"
#include "src/_classdef.h"
#include "src/lib/object.h"


namespace engine {
	class Mouse : public Object {
		friend InputInterface;
	private:
		double curX = 0, curY = 0;
		double lastX = 0, lastY = 0;
		bool inWindow = false;
		bool attachedToCenter = false;

		void updateState(GLFWwindow *window);

	public:
		Mouse(Object *parent = nullptr);

		const Signal<double, double> onMove;
		const Signal<> onLeave;
		const Signal<> onEnter;

		double getCurX() const;
		double getCurY() const;
		double getLastX() const;
		double getLastY() const;
		double getDeltaX() const;
		double getDeltaY() const;
		bool isInWindow() const;

		bool isAttachedToCenter() const;
		void setAttachedToCenter(bool attachedToCenter);

		void attachedToScene(const Scene *pScene);
		void unattachedFromScene(const Scene *pScene);
	};
}

