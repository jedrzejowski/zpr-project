#pragma once

#include "src/_classdef.h"

namespace block {
	class Block {
	protected:
		map::Chunk *chunk = nullptr;
		coord3D position;

	public:
		Block();

		void setPosition(map::Chunk *chunk, const coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		virtual bool isSolid();

		Block *getNeighbor(int64_t dx, int64_t dy, int64_t dz) const;
	};
}

