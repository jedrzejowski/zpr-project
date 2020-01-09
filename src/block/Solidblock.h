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
		bool is_texture_reference_init_required = true;

		explicit SolidBlock() = default;
		explicit SolidBlock(json &data);

		virtual Coord2D getTopTextureCoord() const = 0;
		virtual Coord2D getSideTextureCoord() const = 0;
		virtual Coord2D getBottomTextureCoord() const = 0;

	private:
		void initTextureReferences();
	protected:
		void setIsTextureReferenceInitRequired(bool isTextureReferenceInitRequired);
		bool isTextureReferenceInitRequired() const;

	public:

		void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
							 std::vector<engine::EboTriangle> &indices) override;

		const engine::SquareTextureReference &getTopTextureReference() const;
		const engine::SquareTextureReference &getSideTextureReference() const;
		const engine::SquareTextureReference &getBottomTextureReference() const;

		bool isSolid() override {
			return true;
		};
	};
}

