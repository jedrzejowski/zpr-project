#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

#include "rectangleObj.h"
#include "text.h"

namespace gui {
	enum ButtonState {
		Idle,
		Hover,
		Clicked,
		Disabled
	};

	class Button : public RectangleObj, public std::enable_shared_from_this<Button> {
		std::string label;
		ButtonState state;
		TextPtr text;

	public:

		explicit Button(InterfacePtr interface);

		const std::string &getLabel() const;
		void setLabel(const std::string &label);

		ButtonState getState() const;
		void setState(ButtonState state);

		const std::string& getText();
		void setText(const std::string& text);

		glm::vec2 getBaseSize() override;

		const Signal<> onClicked;
	};
}
