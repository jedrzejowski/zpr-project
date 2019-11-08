#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "light.h"
#include "shaderProgram.h"
#include "window.h"

namespace engine {

	class Scene : public Object {
	private:
		Window *window = nullptr;
		InputInterface *inputInterface = nullptr;
	public:
		const Signal<> onWindowChanged;

		virtual void render(Window *window) = 0;

		Window *getWindow() const;
		void setWindow(Window *window);
		bool isInWindow();

		InputInterface *getInputInterface() const;
		void setInputInterface(InputInterface *inputInterface);

		const Signal<> onRefreshBuffers;
	};
}
