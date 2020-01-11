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
	class WorldRenderer : public Object, public VirtualSharePtrObject<WorldRenderer> {
	private:
		const WorldPtr world_map_ptr;
		WorldShaderPtr shader;

		BackWorkerQueue worker;

		std::map<Coord2D, ChunkRendererPtr> chunk_renderers;

		explicit WorldRenderer(const WorldPtr& worldMap);
		void initEvents();
	public:
		static WorldRendererPtr create(const WorldPtr &worldMap);
		~WorldRenderer() override;

		WorldShaderPtr getShader() const;


		void render(const engine::Camera &camera,
					const engine::ScenePtr& scene);
	};
}