#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"
#include "world.h"

namespace map {
	class WorldRenderer : public Object {
	private:
		const WorldPtr worldMap;
		const engine::Texture *blockTexture = nullptr;
		engine::ShaderProgram *shader = nullptr;

		BackWorkerQueue worker;

		std::list<ChunkRendererPtr> chunkRenderers;

	public:
		explicit WorldRenderer(const WorldPtr& worldMap);
		~WorldRenderer();

		engine::ShaderProgram *getShader() const;

		void injectChunkRenderer(ChunkRendererPtr& chunkRenderer);
		void ejectChunkRenderer(ChunkRendererPtr& chunkRenderer);

		void render(const engine::Camera &camera,
					const engine::ScenePtr scene);

		void syncWithWorld();
	};
}