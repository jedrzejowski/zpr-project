#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace engine {
	class Mouse : public Object {
		friend Window;
	private:
		double curX, curY;
		double lastX, lastY;
		bool inWindow = false;
		bool attachedToCenter;

		int mode;

		void updateState(GLFWwindow *window);

	public:
		Mouse(Window *window = nullptr);

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
	};
}

