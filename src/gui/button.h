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

	class Button : public RectangleObj {
		std::string label;
		ButtonState state;
		Text* text;

	public:

		explicit Button(Interface* interface);

		const std::string &getLabel() const;
		void setLabel(const std::string &label);

		ButtonState getState() const;
		void setState(ButtonState state);
	};
}
