/**
 * @file Water.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {

	/**
	 * @brief Woda
	 */
	class Water : public SolidBlock {
	public:
		explicit Water()= default;
		explicit Water(json& data);
		int typeId() const override;
	protected:
		Coord2D getTopTextureCoord() const override;
		Coord2D getSideTextureCoord() const override;
		Coord2D getBottomTextureCoord() const override;
	};
}

