#pragma once

#include "src/types.h"
#include "src/gengine/gEngine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk {
	protected:
		std::vector<gengine::SimpleTriangle> indicesVec;
		std::map<block::position, block::Block *> blocks;

	public:
		Chunk();
		static const ushort MAX_X = 16, MAX_Y = 16, MAX_Z = 16;

		bool addBlock(const block::position &position, block::Block *block);
		block::Block *getBlock(const block::position &position);
		std::map<block::position, block::Block *> getAllBlocks();
		std::map<block::position, block::Block *> getVisibleBlocks();
	};
}

