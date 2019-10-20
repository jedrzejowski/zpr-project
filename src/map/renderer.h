#pragma once

#include "src/gengine/gEngine.h"
#include "_classdef.h"
#include "worldmap.h"

namespace map {
	class Renderer {
	private:
		const gengine::Texture *blockTexture;
		gengine::Shader *shader;
		gengine::Light *light;

		WorldMap *worldMap;
		std::vector<ChunkRenderer*> chunkRenderers;
	public:
		Renderer(WorldMap *worldMap);
		~Renderer();

		WorldMap *getWorldMap() const;

		void render();
	};
}