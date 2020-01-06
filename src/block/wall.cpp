#include "_classdef.h"
#include "wall.h"

glm::Square block::getWall(Coord3D pos, block::Direction dir) {
	return block::getWall(FullPosition(Coord2D(), pos), dir);
}

glm::Square block::getWall(FullPosition pos, block::Direction dir) {

	auto vec = pos.toVec();

	switch (dir) {

		case Z_PLUS:
			return glm::Square(
					vec + glm::vec3(0, 0, 1),
					vec + glm::vec3(0, 1, 1),
					vec + glm::vec3(1, 1, 1),
					vec + glm::vec3(1, 0, 1)
			);

		case Z_MINUS:
			return glm::Square(
					vec + glm::vec3(0, 0, 0),
					vec + glm::vec3(1, 0, 0),
					vec + glm::vec3(1, 1, 0),
					vec + glm::vec3(0, 1, 0)
			);

		case X_PLUS:
			return glm::Square(
					vec + glm::vec3(1, 0, 0),
					vec + glm::vec3(1, 0, 1),
					vec + glm::vec3(1, 1, 1),
					vec + glm::vec3(1, 1, 0)
			);

		case X_MINUS:
			return glm::Square(
					vec + glm::vec3(0, 0, 0),
					vec + glm::vec3(0, 1, 0),
					vec + glm::vec3(0, 1, 1),
					vec + glm::vec3(0, 0, 1)
			);

		case Y_PLUS:
			return glm::Square(
					vec + glm::vec3(0, 1, 0),
					vec + glm::vec3(1, 1, 0),
					vec + glm::vec3(1, 1, 1),
					vec + glm::vec3(0, 1, 1)
			);

		case Y_MINUS:
			return glm::Square(
					vec + glm::vec3(0, 0, 0),
					vec + glm::vec3(0, 0, 1),
					vec + glm::vec3(1, 0, 1),
					vec + glm::vec3(1, 0, 0)
			);
	}

	throw zprException("enum not matched");
}