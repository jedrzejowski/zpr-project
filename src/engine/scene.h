#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

#include "light.h"
#include "shaderProgram.h"
#include "window.h"

namespace engine {

	class Scene : public Object, public virtual_enable_shared_from_this<Scene> {
	private:
		WindowWPtr window;
		InputInterfacePtr inputInterface;

	protected:
		Scene();

	public:
		const Signal<> onWindowChanged;

		virtual void render(WindowPtr& window) = 0;

		WindowWPtr getWindow() const;
		void setWindow(WindowWPtr window);
		bool isInWindow();

		InputInterfacePtr getInputInterface();
		void setInputInterface(InputInterfacePtr interfacePtr);

		virtual void pollEvents() {};

		const Signal<> onRefreshBuffers;
	};
}
