#pragma once

#include "src/_classdef.h"

namespace block {
	class Block {
	protected:
		map::Chunk *chunk;
		cord3D position;

	public:
		Block();

		void setPosition(map::Chunk *chunk, const cord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::SimpleTriangle> &indices) = 0;
	};
}

