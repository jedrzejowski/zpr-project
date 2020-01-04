//
// Created by adam on 15.10.2019.
//

#include <src/block/Blocks.h>
#include "stone.h"

block::Stone::Stone() : SolidBlock() {
	texTop = Coord2D(1, 3);
	texSide = Coord2D(1, 3);
	texBottom = Coord2D(1, 3);
}

int block::Stone::typeId() {
	return TYPE_ID_STONE;
}
