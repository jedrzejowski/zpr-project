#pragma once

#include "src/_classdef.h"
#include "block.h"
#include "src/engine/textureReference.h"

namespace block {
	class SolidBlock : public Block {
	protected:
		engine::SquareTextureReference texTop;
		engine::SquareTextureReference texSide;
		engine::SquareTextureReference texBottom;

		SolidBlock(
				const Coord2D& top,
				const Coord2D& side,
				const Coord2D& bottom
				);

	public:

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::SimpleTriangle> &indices) override;

		bool isSolid() override {
			return true;
		};
	};
}

