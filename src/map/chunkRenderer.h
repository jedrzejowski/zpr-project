#pragma once

#include "src/_classdef.h"
#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {

	class ChunkRenderer : public Object, public engine::Abs3DObj {
	private:
		Chunk *chunk = nullptr;
		glm::mat4 chunkPos;
		Renderer *renderer = nullptr;

		std::map<coord3D, block::Block *> visibleBlocks;

	protected:

		void updateBuffers() override ;

	public:
		ChunkRenderer(Renderer *renderer, Chunk *chunk);

		void render(const engine::Scene *scene) override;
	};
}