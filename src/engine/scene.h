#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "light.h"
#include "shader.h"
#include "window.h"

namespace engine {

	class Scene : public Object {
	private:
		Window *window;
		Keyboard *keyboard;
		Mouse *mouse;
	public:
		const Signal<> onWindowChanged;

		virtual void render3D(Window *window) = 0;
		virtual void renderGUI(Window *window) = 0;

		Window *getWindow() const;
		void setWindow(Window *window);
		Keyboard *getKeyboard() const;
		void setKeyboard(Keyboard *keyboard);
		Mouse *getMouse() const;
		void setMouse(Mouse *mouse);
	};
}
