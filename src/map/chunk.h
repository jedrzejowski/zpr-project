#pragma once

#include "src/engine/Engine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk {
	protected:
		std::vector<engine::SimpleTriangle> indicesVec;
		std::map<cord3D, block::Block *> blocks;

	public:
		Chunk();

		bool addBlock(const cord3D &position, block::Block *block);
		block::Block *getBlock(const cord3D &position);
		std::map<cord3D, block::Block *> getAllBlocks();
	};
}

