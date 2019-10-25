#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "worldmap.h"
#include "src/lib/object.h"

namespace map {
	class Renderer : public Object {
	private:
		const engine::Texture *blockTexture;
		engine::Shader *shader;

		const WorldMap *worldMap;

		std::vector<ChunkRenderer *> chunkRenderers;
	public:
		explicit Renderer(const WorldMap *worldMap);
		~Renderer();

		engine::Shader *getShader() const;

		void render(const engine::Camera &camera,
					const engine::Scene *scene);
	};
}