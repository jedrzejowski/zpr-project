/**
 * @file Wall.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/lib/glmEx.h"
#include "src/lib/Coord.hpp"
#include "FullPosition.h"

namespace block {
	enum Direction {
		Z_PLUS,
		Z_MINUS,
		X_PLUS,
		X_MINUS,
		Y_PLUS,
		Y_MINUS
	};

	glm::Square getWall(Coord3D pos, Direction dir);
	glm::Square getWall(FullPosition pos, Direction dir);
}