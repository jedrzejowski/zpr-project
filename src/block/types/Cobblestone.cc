/**
 * @file Cobblestone.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Blocks.h>
#include "Cobblestone.h"

block::Cobblestone::Cobblestone(json &data) : SolidBlock(data) {}

int block::Cobblestone::typeId() {
	return TYPE_ID_COBBLESTONE;
}

Coord2D block::Cobblestone::getTopTextureCoord() const {
	return Coord2D(1, 1);
}

Coord2D block::Cobblestone::getSideTextureCoord() const {
	return Coord2D(1, 1);
}

Coord2D block::Cobblestone::getBottomTextureCoord() const {
	return Coord2D(1, 1);
}
