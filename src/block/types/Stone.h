/**
 * @file Stone.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {

	/**
	 * @brief Kamień
	 */
	class Stone : public SolidBlock {
	protected:
		Coord2D getTopTextureCoord() const override;
		Coord2D getSideTextureCoord() const override;
		Coord2D getBottomTextureCoord() const override;
	public:
		explicit Stone() = default;
		explicit Stone(json &data);
		int typeId() const override;
	};
}

