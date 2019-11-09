#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "world.h"
#include "src/lib/object.h"

namespace map {
	class WorldRenderer : public Object {
	private:
		const engine::Texture *blockTexture = nullptr;
		engine::ShaderProgram *shader = nullptr;

		const World *worldMap = nullptr;

		std::vector<ChunkRenderer *> chunkRenderers;
	public:
		explicit WorldRenderer(const World *worldMap);
		~WorldRenderer();

		engine::ShaderProgram *getShader() const;

		void render(const engine::Camera &camera,
					const engine::Scene *scene);
	};
}