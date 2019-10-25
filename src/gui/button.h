#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "guiObj.h"

namespace gui {
	class Button : public GuiObject {
	protected:
		std::string label;

	public:
		Button();
		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;
	};
}
