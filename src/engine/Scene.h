/**
 * @file Scene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.hpp"

#include "Light.h"
#include "ShaderProgram.h"
#include "Window.h"

namespace engine {

	class Scene : public Object, public VirtualSharePtrObject<Scene> {
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
