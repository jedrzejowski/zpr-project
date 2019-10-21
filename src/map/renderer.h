#pragma once

#include "src/engine/Engine.h"
#include "src/_classdef.h"
#include "worldmap.h"

namespace map {
	class Renderer {
	private:
		const engine::Texture *blockTexture;
		engine::Shader *shader;
		engine::Light *light;

		WorldMap *worldMap;
		std::vector<ChunkRenderer*> chunkRenderers;
	public:
		Renderer(WorldMap *worldMap);
		~Renderer();

		WorldMap *getWorldMap() const;

		void render(engine::Scene* scene);
	};
}