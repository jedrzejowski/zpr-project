/**
 * @file Log.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Log.h"
#include "../type_ids.h"


block::Log::Log(json &data) : SolidBlock(data) {
}

int block::Log::typeId() const {
	return TYPE_ID_LOG;
}

Coord2D block::Log::getTopTextureCoord() const {
	return Coord2D(2, 2);
}

Coord2D block::Log::getSideTextureCoord() const {
	return Coord2D(2, 1);
}

Coord2D block::Log::getBottomTextureCoord() const {
	return Coord2D(2, 2);
}
