#pragma once

#include "src/types.h"
#include "src/gengine/gEngine.h"
#include "src/block/Blocks.h"

namespace map {
	class Chunk : public gengine::Abs3DObj {
	protected:
		const gengine::Texture *stoneTex;
		std::vector<gengine::SimpleTriangle> indicesVec;
		std::map<block::position, block::Block *> blocks;

		void initVerticles();
		void initIndicies();
	public:
		Chunk();
		static const ushort MAX_X = 16, MAX_Y = 16, MAX_Z = 16;

		void render(gengine::Window *window) override;

		bool addBlock(const block::position &position, block::Block *block);
		block::Block *getBlock(const block::position &position);

		static uint getVerticleIndex(ushort x, ushort y, ushort z);
	};
}

