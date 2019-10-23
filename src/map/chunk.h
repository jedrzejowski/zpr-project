#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"
#include "src/block/Blocks.h"
#include "Map.h"

namespace map {
	class Chunk : public Object {
		friend ChunkRenderer;
		friend ChunkGenerator;
	protected:
		WorldMap* worldMap;
		const coord2D position;
		std::vector<engine::SimpleTriangle> indicesVec;
		std::map<coord3D, block::Block *> blocks;

	public:
		static const coord3D Size;

		Chunk(WorldMap* worldMap, const coord2D &position);

		bool addBlock(const coord3D &position, block::Block *block);
		block::Block *getBlock(const coord3D &position);
		std::map<coord3D, block::Block *> getAllBlocks();

		const coord2D &getPosition() const;
		Chunk * getNeighbor(int64_t dx, int64_t dy) const;

	};
}

