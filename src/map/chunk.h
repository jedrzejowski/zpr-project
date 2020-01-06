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
		std::map<Coord3D, block::BlockPtr> blocks;

	public:
		static const Coord3D Size;

		Chunk(World *worldMap, const Coord2D &position);
		~Chunk() override;

		bool setBlock(const Coord3D &position, block::BlockPtr &block);
		bool setAir(const Coord3D &position);
		bool isAir(const Coord3D &position);
		block::BlockPtr getBlock(const Coord3D &position);
		const std::map<Coord3D, block::BlockPtr> &getAllBlocks() const;

		const Coord2D &getPosition() const;
		ChunkWPtr getNeighbor(CoordDim dx, CoordDim dy) const;

		json toJSON() const;

		const Signal<const Coord3D &> onBlockChange;

		void save();
	};
}

