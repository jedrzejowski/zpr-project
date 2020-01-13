/**
 * @file Log.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Solidblock.h"

namespace block {

	/**
	 * @brief Kłoda
	 */
	class Log : public SolidBlock {
	public:
		explicit Log()= default;
		explicit Log(json& data);
		int typeId() const override;
	protected:
		Coord2D getTopTextureCoord() const override;
		Coord2D getSideTextureCoord() const override;
		Coord2D getBottomTextureCoord() const override;
	};
}