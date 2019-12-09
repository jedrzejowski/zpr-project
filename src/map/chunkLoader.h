#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"
#include "src/lib/object.h"
#include "src/lib/backWorkerQueue.h"
#include "world.h"

namespace map {


	class ChunkLoader : public Object {
		friend World;
	private:
		World *world;
		WorldRenderer *renderer;
		BackWorkerQueue worker;
		ChunkGenerator chunkGenerator;

		std::list<Coord2D> loadingChunksCoords;
		std::list<Coord2D> unloadingChunksCoords;

		std::mutex chunkListAccess;
		std::list<map::ChunkPtr > chunksToRemove;
		std::list<map::ChunkPtr > chunksToAdd;

		ChunkPtr readChunkFromFile(const Coord2D &coord);
		ChunkPtr generateNewChunk(const Coord2D &coord);
		void saveChunkToFile(ChunkPtr chunk);

	public:
		explicit ChunkLoader(World *world);
		~ChunkLoader() override;

		void load(Coord2D coord);
		void unload(Coord2D coord);

		bool isChunkLoaded(const Coord2D &coord);
		bool isChunkLoading(const Coord2D &coord);
		bool isChunkUnloading(const Coord2D &coord);

		void syncWithWorld();
	};
}

