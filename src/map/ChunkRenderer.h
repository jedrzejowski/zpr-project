/**
 * @file ChunkRenderer.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/block/Blocks.h"
#include "src/engine/Engine.h"
#include "src/lib/Object.hpp"

namespace map {

	class ChunkRenderer : public Object, public engine::Abs3DObj {
	private:
		const ChunkPtr chunk;
		glm::mat4 chunk_position_matrix{};
		WorldRendererWPtr world_renderer_wptr;

		explicit ChunkRenderer(WorldRendererPtr& renderer, const ChunkPtr& chunkPtr);
		void constructorChunkRenderer();
	public:
		static ChunkRendererPtr create(WorldRendererPtr& renderer, const ChunkPtr& chunkPtr);
		~ChunkRenderer() override;

		void updateBuffers() override;

		ChunkRendererWPtr getNeighbor(CoordDim dx, CoordDim dy) const;


		void render(const engine::ScenePtr& scene) override;
	};
}