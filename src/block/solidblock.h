#pragma once

#include "src/_classdef.h"
#include "block.h"

namespace block {
	class SolidBlock : public Block {
	protected:
		Coord2D texTop;
		Coord2D texSide;
		Coord2D texBottom;
	public:

		SolidBlock();

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;

		bool isSolid() override {
			return true;
		};
	};
}

