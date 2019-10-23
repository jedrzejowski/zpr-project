#include "worldmap.h"
#include "chunk.h"

map::WorldMap::WorldMap() {
}

map::Chunk *map::WorldMap::getChunk(const coord2D &position) const {
	if (chunks.count(position) == 1)
		return chunks[position];
	return nullptr;
}

map::Chunk *map::WorldMap::genChunk(int x, int y) {
	return nullptr;
}

bool map::WorldMap::loadChunk(const coord2D& position) {
	return false;
}

void map::WorldMap::setChunk(map::Chunk *chunk) {
	chunks[chunk->getPosition()] = chunk;

	visibleChunks.push_back(chunk);
}

const std::vector<map::Chunk *> &map::WorldMap::getVisibleChunk() const {
	return visibleChunks;
}
