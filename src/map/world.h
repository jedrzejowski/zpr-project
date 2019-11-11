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
		std::map<Coord2D, Chunk *> chunks;

	public:
		World();

		bool hasChunk(const Coord2D &position);
		Chunk *getChunk(const Coord2D &position);
		Chunk *ejectChunk(const Coord2D &position);
		void insertChunk(Chunk *chunk);

		void requestChunk(Coord2D position);

		void syncChunkWithLoader();

		const Signal<Chunk *> onChunkInserted;
		const Signal<Chunk *> onChunkEjected;
	};
}
