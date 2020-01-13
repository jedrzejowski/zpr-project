/**
 * @file Wood.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Blocks.h>
#include "Wood.h"

block::Wood::Wood(json &data) : SolidBlock(data) {}

int block::Wood::typeId() const {
	return TYPE_ID_WOOD;
}

Coord2D block::Wood::getTopTextureCoord() const {
	return Coord2D(3, 2);
}

Coord2D block::Wood::getSideTextureCoord() const {
	return Coord2D(3, 2);
}

Coord2D block::Wood::getBottomTextureCoord() const {
	return Coord2D(3, 2);
}
