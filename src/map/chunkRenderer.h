#pragma once

#include "src/_classdef.h"
#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {

	class ChunkRenderer : public Object, public engine::Abs3DObj {
	private:
		ChunkPtr chunk;
		glm::mat4 chunkPos;
		WorldRenderer *worldRenderer = nullptr;

		std::map<Coord3D, block::Block *> visibleBlocks;

	public:
		explicit ChunkRenderer(WorldRenderer *renderer, ChunkPtr chunk);

		void updateBuffers() override;

		void render(const engine::ScenePtr scene) override;
	};
}