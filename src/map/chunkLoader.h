#pragma once

#include "src/_classdef.h"
#include "src/lib/coord.h"
#include "src/lib/object.h"
#include "src/lib/backWorkerQueue.h"
#include "chunkGenerator.h"

namespace map {


	class ChunkLoader : public Object {
		friend World;
	private:
		World* world;
		BackWorkerQueue worker;

		std::list<Coord2D> chunksToRemove;
		std::list<Coord2D> unloadingChunksCoords;


		std::list<Coord2D> loadingChunksCoords;
		std::list<map::ChunkPtr> chunksToAdd;


		std::mutex chunkListAccess;

		ChunkPtr readChunkFromFile(const Coord2D &coord);
		ChunkPtr generateNewChunk(const Coord2D &coord);
		void saveChunkToFile(ChunkPtr chunk);

	public:
		explicit ChunkLoader(World* world);
		~ChunkLoader() override;

		void load(Coord2D coord);
		void unload(Coord2D coord);

		bool isChunkLoaded(const Coord2D &coord);
		bool isChunkLoading(const Coord2D &coord);
		bool isChunkUnloading(const Coord2D &coord);

		void syncWithWorld();
	};
}

