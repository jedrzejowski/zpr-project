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
		InputInterfacePtr inputInterface;

	protected:
		Scene();

	public:
		const Signal<> onWindowChanged;

		virtual void render(Window *window) = 0;

		Window *getWindow() const;
		void setWindow(Window *window);
		bool isInWindow();

		InputInterfacePtr getInputInterface();
		void setInputInterface(InputInterfacePtr interfacePtr);

		virtual void pollEvents() {};

		const Signal<> onRefreshBuffers;
	};
}
