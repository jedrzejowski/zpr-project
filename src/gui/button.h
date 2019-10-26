#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "guiObj.h"

namespace gui {
	enum ButtonState {
		Idle,
		Hover,
		Clicked,
		Disabled
	};

	class Button : public GuiObject {
	private:
		std::string label;

		ButtonState state;

	public:
		explicit Button(Object* parent = nullptr);
		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;

		const std::string &getLabel() const;
		void setLabel(const std::string &label);

		ButtonState getState() const;
		void setState(ButtonState state);
	};
}
