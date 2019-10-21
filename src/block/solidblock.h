#pragma once

#include "src/_classdef.h"
#include "block.h"

namespace block {
	class SolidBlock : public Block {
	protected:
		cord2D texTop;
		cord2D texSide;
		cord2D texBottom;
	public:

		SolidBlock();

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;
	};
}

