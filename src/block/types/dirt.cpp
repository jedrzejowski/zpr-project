#include <src/block/Blocks.h>
#include "dirt.h"

block::Dirt::Dirt() {
	texTop = Coord2D(1, 2);
	texSide = Coord2D(1, 2);
	texBottom = Coord2D(1, 2);
}

int block::Dirt::typeId() {
	return TYPE_ID_DIRT;
}
