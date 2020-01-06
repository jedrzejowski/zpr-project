#include <src/block/Blocks.h>
#include "dirt.h"

block::Dirt::Dirt() :
		SolidBlock(
				Coord2D(1, 2),
				Coord2D(1, 2),
				Coord2D(1, 2)
		) {
}

int block::Dirt::typeId() {
	return TYPE_ID_DIRT;
}
