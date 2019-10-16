#pragma once

#include <map>

#include "_class.h"

namespace map {
	class WorldMap {
	protected:
		std::map<ChunkPos, Chunk *> chunks;

		Chunk *genChunk(int x, int y);
	public:
		WorldMap();
		void setChunk(int x, int y, Chunk *chunk);

		Chunk *getChunk(int x, int y);
		bool loadChunk(int x, int y);
	};
}
