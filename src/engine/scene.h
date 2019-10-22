#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "light.h"
#include "shader.h"
#include "window.h"

namespace engine {

	class Scene : public Object {
	protected:
		Window *window;
	public:
		Window *getWindow() const;
		void setWindow(Window *window);
		const Signal<> onWindowChanged;

		virtual void render3D(Window *window) = 0;
		virtual void renderGUI(Window *window) = 0;
	};
}
