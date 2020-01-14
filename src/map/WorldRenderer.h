/**
 * @file WorldRenderer.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/Object.hpp"
#include "World.h"

namespace map {

	/**
	 * @brief Obiekt renderujący świat
	 */
	class WorldRenderer : public Object, public VirtualSharePtrObject<WorldRenderer> {
	public:
		using VirtualSharePtrObject<WorldRenderer>::shared_from_this;
		using VirtualSharePtrObject<WorldRenderer>::weak_from_this;
	private:
		const WorldPtr world_map_ptr;
		WorldShaderPtr shader;

		std::map<Coord2D, ChunkRendererPtr> chunk_renderers;

		explicit WorldRenderer(const WorldPtr& worldMap);
		void constructorWorldRenderer();
	public:
		static WorldRendererPtr create(const WorldPtr &worldMap);
		~WorldRenderer() override;

		WorldShaderPtr getShader() const;

		ChunkRendererWPtr getChunkRenderer(const Coord2D& position);

		void render(const engine::Camera &camera,
					const engine::ScenePtr& scene);
	};
}