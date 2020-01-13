/**
 * @file Dirt.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {
	class Dirt : public SolidBlock {
	protected:
		Coord2D getTopTextureCoord() const override;
		Coord2D getSideTextureCoord() const override;
		Coord2D getBottomTextureCoord() const override;
	public:
		explicit Dirt() = default;
		Dirt(json &data);
		int typeId() const override;
	};
}

