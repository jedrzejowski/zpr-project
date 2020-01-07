/**
 * @file FullPosition.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "src/lib/Coord.hpp"

namespace block {
	class FullPosition {
		Coord2D chunk;
		Coord3D block;
	public:
		FullPosition();
		FullPosition(const Coord2D &chunk, const Coord3D &block);

		const Coord2D &getChunk() const;
		void setChunk(const Coord2D &chunk);
		const Coord3D &getBlock() const;
		void setBlock(const Coord3D &block);

		bool isValid();

		glm::vec3 toVec() const;

		FullPosition getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};
}

inline std::ostream &operator<<(std::ostream &out, const block::FullPosition &pos) {
	return out << "block::FullPosition(chunk:" << pos.getChunk() << ", block:" << pos.getBlock() << ")";
}

inline bool operator==(const block::FullPosition &left, const block::FullPosition &right) {
	return left.getChunk() == right.getChunk() && left.getBlock() == right.getBlock();
}