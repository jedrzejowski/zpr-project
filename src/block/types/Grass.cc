/**
 * @file Grass.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Grass.h"
#include "../type_ids.h"

block::Grass::Grass(json &data) : SolidBlock(data) {}

int block::Grass::typeId() {
	return TYPE_ID_GRASS;
}

Coord2D block::Grass::getTopTextureCoord() const {
	return Coord2D(2, 4);
}

Coord2D block::Grass::getSideTextureCoord() const {
	return Coord2D(1, 2);
}

Coord2D block::Grass::getBottomTextureCoord() const {
	return Coord2D(1, 2);
}
