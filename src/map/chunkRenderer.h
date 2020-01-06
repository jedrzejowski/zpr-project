#pragma once

#include "src/_classdef.h"
#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {

	class ChunkRenderer : public Object, public engine::Abs3DObj {
	private:
		const ChunkPtr chunk;
		glm::mat4 chunkPos{};
		WorldRendererWPtr worldRenderer;

		explicit ChunkRenderer(WorldRendererPtr& renderer, const ChunkPtr& chunkPtr);
		void initEvents();
	public:
		static ChunkRendererPtr create(WorldRendererPtr& renderer, const ChunkPtr& chunkPtr);
		~ChunkRenderer() override;

		void updateBuffers() override;

		void render(const engine::ScenePtr scene) override;
	};
}