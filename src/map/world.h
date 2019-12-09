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
		ChunkLoader *chunkLoader;
		std::map<Coord2D, map::ChunkPtr> chunks;

	public:
		World();

		bool hasChunk(const Coord2D &position);
		ChunkPtr getChunk(const Coord2D &position);
		ChunkPtr ejectChunk(const Coord2D &position);
		void insertChunk(map::ChunkPtr chunk);

		void requestChunk(Coord2D position);

		void syncChunkWithLoader();

		const Signal<ChunkPtr > onChunkInserted;
		const Signal<ChunkPtr > onChunkEjected;
	};
}
