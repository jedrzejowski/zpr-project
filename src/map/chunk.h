#pragma once

#include "src/engine/Engine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk {
		friend ChunkRenderer;
		friend ChunkGenerator;
	protected:
		coord2D position;
		std::vector<engine::SimpleTriangle> indicesVec;
		std::map<coord3D, block::Block *> blocks;

	public:
		static const coord3D Size;

		Chunk(const coord2D &position);

		bool addBlock(const coord3D &position, block::Block *block);
		block::Block *getBlock(const coord3D &position);
		std::map<coord3D, block::Block *> getAllBlocks();

		const coord2D &getPosition() const;
	};
}

