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
		BackWorkerQueue worker;
		ChunkGenerator chunkGenerator;

		std::vector<Chunk *> chunksToRemove;
		std::vector<Chunk *> chunksToAdd;
	public:
		explicit ChunkLoader(World *world);
		~ChunkLoader() override;

		void load(Coord2D coord);
		void unload(Coord2D coord);

		void syncWithWorld();
	};
}

