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
	 * @brief Piasek, ale bez fizyki
	 */
	class Sand : public SolidBlock {
	protected:
		Coord2D getTopTextureCoord() const override;
		Coord2D getSideTextureCoord() const override;
		Coord2D getBottomTextureCoord() const override;
	public:
		explicit Sand() = default;
		explicit Sand(json &data);
		int typeId() const override;
	};
}

