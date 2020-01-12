/**
 * @file Chunk.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/SavableObject.h"
#include "src/lib/Coord.hpp"
#include "src/lib/Object.hpp"
#include "src/engine/Engine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk : public Object, public VirtualSharePtrObject<Chunk>, public SavableObject {
	public:
		using VirtualSharePtrObject<Chunk>::shared_from_this;
		using VirtualSharePtrObject<Chunk>::weak_from_this;
		friend ChunkRenderer;
		friend ChunkGenerator;
		friend ChunkLoader;
	private:

		const WorldWPtr world_map_wptr;
		const Coord2D position;
		mutable std::map<Coord3D, block::BlockPtr> blocks;

		Chunk(const WorldPtr &worldMap, const Coord2D &position);

	public:
		static const Coord3D Size;

		static ChunkPtr create(const WorldPtr &worldMap, const Coord2D &position);

		~Chunk() override;

		bool setBlock(const Coord3D &position, block::BlockPtr &block);
		bool setAir(const Coord3D &position);
		bool isAir(const Coord3D &position) const;
		block::BlockPtr getBlock(const Coord3D &position) const;
		const std::map<Coord3D, block::BlockPtr> &getAllBlocks() const;

		const Coord2D &getPosition() const;
		ChunkWPtr getNeighbor(CoordDim dx, CoordDim dy) const;

		const Signal<const Coord3D &> onBlockChange;

		//region SavableObject

	protected:
		void acceptState(json &data) override;
	public:
		boost::filesystem::path getSavePath(AppSettings &app_settings) const override;
		json toJSON() const override;

		//endregion
	};
}

