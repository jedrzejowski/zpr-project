#pragma once

#include <map>
#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace map {
	class WorldMap : public Object {
	protected:
		mutable std::map<coord2D, Chunk *> chunks;
		std::vector<Chunk *> visibleChunks;

		Chunk *genChunk(int x, int y);
	public:
		WorldMap();
		void setChunk(Chunk *chunk);

		Chunk *getChunk(const coord2D& position) const;
		const std::vector<Chunk *>& getVisibleChunk() const;
		bool loadChunk(const coord2D& position);
	};
}
