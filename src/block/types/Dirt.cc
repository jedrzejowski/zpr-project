#include "Dirt.h"
#include "../type_ids.h"

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
