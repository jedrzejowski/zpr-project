#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk : public Object, public virtual_enable_shared_from_this<Chunk> {
		friend ChunkRenderer;
		friend ChunkGenerator;
		friend ChunkLoader;
	protected:
		World *worldMap;
		const Coord2D position;
		std::map<Coord3D, block::Block *> blocks;

	public:
		static const Coord3D Size;

		Chunk(World *worldMap, const Coord2D &position);
		~Chunk() override;

		bool setBlock(const Coord3D &position, block::Block *block);
		block::Block *getBlock(const Coord3D &position);
		std::map<Coord3D, block::Block *> &getAllBlocks();

		const Coord2D &getPosition() const;
		ChunkWPtr getNeighbor(CoordDim dx, CoordDim dy) const;

		json toJSON() const;

		void save();
	};
}

