//
// Created by adam on 15.10.2019.
//

#include <src/block/Blocks.h>
#include "stone.h"

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
