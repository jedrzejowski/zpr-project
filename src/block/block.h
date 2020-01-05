#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"

namespace block {



	class Block {
	protected:
		map::Chunk *chunk;
		Coord3D position;

	public:
		static const float TexColumns;
		static const float TexRows;
		static std::tuple<glm::vec2, glm::vec2> getBlockText(int x, int y);

		Block();

		void setPosition(map::Chunk *chunk, const Coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;

		virtual bool isSolid();

		virtual json toJSON();

		virtual int typeId() = 0;

		Block *getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};
}

