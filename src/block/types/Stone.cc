/**
 * @file Stone.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Blocks.h>
#include "Stone.h"

block::Stone::Stone(json &data) : SolidBlock(data) {}

int block::Stone::typeId() const {
	return TYPE_ID_STONE;
}

Coord2D block::Stone::getTopTextureCoord() const {
	return Coord2D(1, 3);
}

Coord2D block::Stone::getSideTextureCoord() const {
	return Coord2D(1, 3);
}

Coord2D block::Stone::getBottomTextureCoord() const {
	return Coord2D(1, 3);
}
