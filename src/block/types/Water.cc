/**
 * @file Water.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Water.h"
#include "../type_ids.h"

block::Water::Water() :
		SolidBlock(
				Coord2D(3, 1),
				Coord2D(3, 1),
				Coord2D(3, 1)
		) {
}

int block::Water::typeId() {
	return TYPE_ID_WATER;
}
