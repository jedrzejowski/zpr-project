/**
 * @file Water.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Water.h"
#include "../type_ids.h"


block::Water::Water(json &data) : SolidBlock(data) {
}

int block::Water::typeId() {
	return TYPE_ID_WATER;
}

Coord2D block::Water::getTopTextureCoord() const {
	return Coord2D(3, 1);
}

Coord2D block::Water::getSideTextureCoord() const {
	return Coord2D(3, 1);
}

Coord2D block::Water::getBottomTextureCoord() const {
	return Coord2D(3, 1);
}
