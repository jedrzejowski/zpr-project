/**
 * @file Dirt.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Dirt.h"
#include "../type_ids.h"

block::Dirt::Dirt(json &data) : SolidBlock(data) {}

int block::Dirt::typeId() {
	return TYPE_ID_DIRT;
}

Coord2D block::Dirt::getTopTextureCoord() const {
	return Coord2D(1, 2);
}

Coord2D block::Dirt::getSideTextureCoord() const {
	return Coord2D(1, 2);
}

Coord2D block::Dirt::getBottomTextureCoord() const {
	return Coord2D(1, 2);
}
