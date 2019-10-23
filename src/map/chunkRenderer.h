#pragma once

#include "src/_classdef.h"
#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {

	class ChunkRenderer : public Object, public engine::Abs3DObj {
	private:
		Chunk *chunk;
		glm::mat4 chunkPos;
		Renderer *renderer;

		std::map<coord3D, block::Block *> visibleBlocks;

	protected:

		void initVerticles();

	public:
		ChunkRenderer(Renderer *renderer, Chunk *chunk);

		void render(engine::Scene *scene) override;
	};
}