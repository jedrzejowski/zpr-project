//
// Created by adam on 15.10.2019.
//

#include <src/block/Blocks.h>
#include "Water.h"

block::Water::Water() :
		SolidBlock(
				Coord2D(1, 3),
				Coord2D(1, 3),
				Coord2D(1, 3)
		) {
}

int block::Water::typeId() {
	return TYPE_ID_WATER;
}
