#pragma once

#include <map>
#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"
#include "chunkGenerator.h"
#include "chunkLoader.h"

namespace map {
	class World : public Object {
	protected:
		ChunkLoader* chunkLoader;
		std::map<Coord2D, Chunk *> chunks;

	public:
		World();
		void setChunk(Chunk *chunk);

		Chunk *getChunk(Coord2D position);

		void requestChunk(Coord2D position);

		void syncChunkWithLoader();
	};
}
