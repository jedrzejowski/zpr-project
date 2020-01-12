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

	class Button : public RectangleObj, public VirtualSharePtrObject<Button> {
	public:
		using VirtualSharePtrObject<Button>::shared_from_this;
		float text_size;
		ButtonState state;
		TextPtr text;

	protected:
		explicit Button(InterfacePtr &interface);
		explicit Button(GuiObjectPtr &gui_object);
		void constructorButton();

		void updateTextModel();

	public:
		static ButtonPtr create(InterfacePtr interface);
		static ButtonPtr create(GuiObjectPtr gui_object);

		void updateBuffers() override;

		ButtonState getState() const;
		void setState(ButtonState state);

		const std::string &getText() const;
		void setText(const std::string &new_text);
		float getTextSize() const;
		void setTextSize(float textSize);

		glm::vec2 getBaseSize() override;

		const Signal<> onClicked;
	};
}
