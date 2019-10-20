#pragma once

#include <map>
#include "src/gengine/gEngine.h"
#include "_classdef.h"

namespace map {
	class WorldMap {
	protected:
		std::map<ChunkPos, Chunk *> chunks;
		std::vector<Chunk *> visibleChunks;

		Chunk *genChunk(int x, int y);
	public:
		WorldMap();
		void setChunk(int x, int y, Chunk *chunk);

		Chunk *getChunk(int x, int y);
		const std::vector<Chunk *>& getVisibleChunk();
		bool loadChunk(int x, int y);
	};
}
