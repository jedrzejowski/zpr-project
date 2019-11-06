#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace gui {
	class GuiObject : public Object, public engine::Sub3DObj {
	private:
		glm::mat4 model = glm::mat4(1);
		Interface *interface = nullptr;
		GuiObject *guiParent = nullptr;
	public:

		explicit GuiObject(Interface *interface);
		explicit GuiObject(GuiObject *parent);

		const glm::mat4 &getModel() const;
		void setModel(const glm::mat4 &model);

		const Interface *getInterface() const;
		Interface *getInterface();

		const Signal<> onHover;
		const Signal<> onEnter;
		const Signal<> onLeave;
		const Signal<> onPressed;
		const Signal<> onReleased;
	};
}


