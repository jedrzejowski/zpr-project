#pragma once

#include <map>
#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"
#include "chunkGenerator.h"

namespace map {
	class WorldMap : public Object {
	protected:
		// wywalić muatble
		mutable ChunkGenerator chunkGenerator;
		mutable std::map<coord2D, Chunk *> chunks;


		Chunk *genChunk(const coord2D& coord);
	public:
		WorldMap();
		void setChunk(Chunk *chunk);

		Chunk *getChunk(const coord2D& position) const;
		bool loadChunk(const coord2D& position) const;
	};
}
