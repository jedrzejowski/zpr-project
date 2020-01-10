/**
 * @file Brick.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Brick.h"
#include "../type_ids.h"

block::Brick::Brick(json &data) : SolidBlock(data) {}

int block::Brick::typeId() {
	return TYPE_ID_BRICK;
}

Coord2D block::Brick::getTopTextureCoord() const {
	return Coord2D(2, 3);
}

Coord2D block::Brick::getSideTextureCoord() const {
	return Coord2D(2, 3);
}

Coord2D block::Brick::getBottomTextureCoord() const {
	return Coord2D(2, 3);
}