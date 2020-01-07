/**
 * @file Stone.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Sand.h"
#include "../type_ids.h"

block::Sand::Sand() :
		SolidBlock(
				Coord2D(1, 4),
				Coord2D(1, 4),
				Coord2D(1, 4)
		) {
}

int block::Sand::typeId() {
	return TYPE_ID_SAND;
}
