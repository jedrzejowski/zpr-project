/**
 * @file Solidblock.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "Block.h"
#include "src/engine/TextureReference.h"

namespace block {
	class SolidBlock : public Block {
	protected:
		engine::SquareTextureReference texture_top;
		engine::SquareTextureReference texture_side;
		engine::SquareTextureReference texture_bottom;

		SolidBlock(
				const Coord2D& top,
				const Coord2D& side,
				const Coord2D& bottom
				);

	public:

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::EboTriangle> &indices) override;

		const engine::SquareTextureReference &getTextureTop() const;
		const engine::SquareTextureReference &getTextureSide() const;
		const engine::SquareTextureReference &getTextureBottom() const;

		bool isSolid() override {
			return true;
		};
	};
}

