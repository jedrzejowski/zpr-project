#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"
#include "world.h"

namespace map {
	class WorldRenderer : public Object {
	private:
		const World *worldMap = nullptr;
		const engine::Texture *blockTexture = nullptr;
		engine::ShaderProgram *shader = nullptr;

		BackWorkerQueue worker;

		std::list<ChunkRenderer *> chunkRenderers;

	public:
		explicit WorldRenderer(const World *worldMap);
		~WorldRenderer();

		engine::ShaderProgram *getShader() const;

		void injectChunkRenderer(ChunkRenderer *chunkRenderer);
		void ejectChunkRenderer(ChunkRenderer *chunkRenderer);

		void render(const engine::Camera &camera,
					const engine::Scene *scene);

		void syncWithWorld();
	};
}