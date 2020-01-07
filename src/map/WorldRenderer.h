#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/Object.hpp"
#include "World.h"

namespace map {
	class WorldRenderer : public Object, public virtual_enable_shared_from_this<WorldRenderer> {
	private:
		const WorldPtr worldMap;
		const engine::Texture *blockTexture = nullptr;
		WorldShaderPtr shader;

		BackWorkerQueue worker;

		std::map<Coord2D, ChunkRendererPtr> chunkRenderers;

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