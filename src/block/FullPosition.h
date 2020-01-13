/**
 * @file FullPosition.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "src/lib/Coord.hpp"

namespace block {

	/**
	 * @brief Implementacja Pełnej pozycji bloku
	 *
	 * Bloki nie posiadają jednej współrzędnej, posiadają współrzędna chunk'a i współrzędną w chunk'u.
	 * Dzięki temu mapa ma wielkość (2^(C+4))x(2^(C+4)), gdzie C to ilość bitów CoordDim
	 *
	 */
	class FullPosition {
		Coord2D chunk;
		Coord3D block;
	public:
		FullPosition();
		FullPosition(const Coord2D &chunk, const Coord3D &block);

		[[nodiscard]] const Coord2D &getChunkCoord() const;
		void setChunk(const Coord2D &chunk);
		[[nodiscard]] const Coord3D &getBlockCoord() const;
		void setBlockCoord(const Coord3D &block);

		bool isValid();

		[[nodiscard]] glm::vec3 toVec() const;

		[[nodiscard]] FullPosition getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};
}

inline std::ostream &operator<<(std::ostream &out, const block::FullPosition &pos) {
	return out << "solid_block::FullPosition(chunk:" << pos.getChunkCoord() << ", solid_block:" << pos.getBlockCoord() << ")";
}

inline bool operator==(const block::FullPosition &left, const block::FullPosition &right) {
	return left.getChunkCoord() == right.getChunkCoord() && left.getBlockCoord() == right.getBlockCoord();
}

inline bool operator!=(const block::FullPosition &left, const block::FullPosition &right) {
	return left.getChunkCoord() != right.getChunkCoord() || left.getBlockCoord() != right.getBlockCoord();
}