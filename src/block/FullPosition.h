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

		const Coord2D &getChunkCoord() const;
		void setChunk(const Coord2D &chunk);
		const Coord3D &getBlockCoord() const;
		void setBlockCoord(const Coord3D &block);

		bool isValid();

		glm::vec3 toVec() const;

		FullPosition getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};
}

inline std::ostream &operator<<(std::ostream &out, const block::FullPosition &pos) {
	return out << "solid_block::FullPosition(chunk:" << pos.getChunkCoord() << ", solid_block:" << pos.getBlockCoord() << ")";
}

inline bool operator==(const block::FullPosition &left, const block::FullPosition &right) {
	return left.getChunkCoord() == right.getChunkCoord() && left.getBlockCoord() == right.getBlockCoord();
}