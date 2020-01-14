/**
 * @file GuiObject.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "src/engine/Engine.h"

namespace gui {

	/**
	 * @brief Obiekt jakieś kontrolki graficznej
	 */
	class GuiObject : public Object, public engine::Sub3DObj {
	private:
		glm::mat4 model = glm::mat4(1);
		InterfaceWPtr interface;
		GuiObjectWPtr guiParent;
	public:

		explicit GuiObject(InterfacePtr interface);
		explicit GuiObject(GuiObjectPtr parent);

		glm::mat4 getModel() const;
		void setModel(const glm::mat4 &model);

		InterfacePtr getInterface() const;
		InterfacePtr getInterface();

		GuiObjectPtr getGuiParent() const;

		const Signal<> onHover;
		const Signal<> onEnter;
		const Signal<> onLeave;
		const Signal<> onPressed;
		const Signal<> onReleased;
	};
}


