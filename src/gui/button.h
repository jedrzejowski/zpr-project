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

	class Button : public RectangleObj,  public virtual_enable_shared_from_this<Button> {
		ButtonState state;
		TextPtr text;

	private:
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
