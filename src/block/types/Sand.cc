/**
 * @file Stone.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Sand.h"
#include "../type_ids.h"


block::Sand::Sand(json &data) : SolidBlock(data) {}

int block::Sand::typeId() const {
	return TYPE_ID_SAND;
}

Coord2D block::Sand::getTopTextureCoord() const {
	return Coord2D(1, 4);
}

Coord2D block::Sand::getSideTextureCoord() const {
	return Coord2D(1, 4);
}

Coord2D block::Sand::getBottomTextureCoord() const {
	return Coord2D(1, 4);
}