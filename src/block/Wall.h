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

	/**
	 * @brief Reprezentacja stron bloku
	 */
	enum Direction {
		Z_PLUS,
		Z_MINUS,
		X_PLUS,
		X_MINUS,
		Y_PLUS,
		Y_MINUS
	};

	/**
	 * @brief Tworzy kwadrat w 3D dla danej ściany bloku
	 * @param pos pozycja bloku
	 * @param dir strona bloku
	 * @return
	 */
	glm::Square getWall(Coord3D pos, Direction dir);

	/**
	 * @brief Tworzy kwadrat w 3D dla danej ściany bloku
	 * @param pos pozycja bloku
	 * @param dir strona bloku
	 * @return
	 */
	glm::Square getWall(FullPosition pos, Direction dir);
}