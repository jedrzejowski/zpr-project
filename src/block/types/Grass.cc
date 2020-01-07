#include "Grass.h"
#include "../type_ids.h"

block::Grass::Grass() :
		SolidBlock(
				Coord2D(2, 4),
				Coord2D(1, 2),
				Coord2D(1, 2)
		) {
}

int block::Grass::typeId() {
	return TYPE_ID_GRASS;
}
