#pragma once


#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/_classdef.h"

namespace map {

	class ChunkRenderer : public engine::Abs3DObj {
	private:
		Chunk *chunk;

		std::map<cord3D, block::Block *> visibleBlocks;

	protected:

		void initVerticles();

	public:
		ChunkRenderer(Chunk *chunk);

		void render(engine::Scene *scene) override;
	};
}