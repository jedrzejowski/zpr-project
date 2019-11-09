#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"

namespace block {
	class Block {
	protected:
		map::Chunk *chunk = nullptr;
		Coord3D position;

	public:
		Block();

		void setPosition(map::Chunk *chunk, const Coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		virtual bool isSolid();

		Block *getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};
}

