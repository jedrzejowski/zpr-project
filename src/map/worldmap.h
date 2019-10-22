#pragma once

#include <map>
#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {
	class WorldMap : public Object {
	protected:
		mutable std::map<ChunkPos, Chunk *> chunks;
		std::vector<Chunk *> visibleChunks;

		Chunk *genChunk(int x, int y);
	public:
		WorldMap();
		void setChunk(int x, int y, Chunk *chunk);

		Chunk *getChunk(int x, int y) const;
		const std::vector<Chunk *>& getVisibleChunk() const;
		bool loadChunk(int x, int y);
	};
}
