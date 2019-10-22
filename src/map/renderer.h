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
		engine::Light *light;

		WorldMap *worldMap;
		std::vector<ChunkRenderer*> chunkRenderers;
	public:
		explicit Renderer(WorldMap *worldMap);
		~Renderer();

		WorldMap *getWorldMap() const;

		void render(engine::Scene* scene);
	};
}