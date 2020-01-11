/**
 * @file Button.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

#include "RectangleObj.h"
#include "Text.h"

namespace gui {
	enum ButtonState {
		Idle,
		Hover,
		Clicked,
		Disabled
	};

	class Button : public RectangleObj,  public VirtualSharePtrObject<Button> {
		ButtonState state;
		TextPtr text;

	protected:
		explicit Button(InterfacePtr& interface);

	public:
		static ButtonPtr create(InterfacePtr interface);

		ButtonState getState() const;
		void setState(ButtonState state);

		const std::string& getText();
		void setText(const std::string& text);

		glm::vec2 getBaseSize() override;

		const Signal<> onClicked;
	};
}
