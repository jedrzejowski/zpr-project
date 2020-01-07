/**
 * @file Stone.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Blocks.h>
#include "Stone.h"

block::Stone::Stone() :
		SolidBlock(
				Coord2D(1, 3),
				Coord2D(1, 3),
				Coord2D(1, 3)
		) {
}

int block::Stone::typeId() {
	return TYPE_ID_STONE;
}
