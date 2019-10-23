#include "worldmap.h"
#include "chunk.h"

map::WorldMap::WorldMap() {
}

map::Chunk *map::WorldMap::getChunk(const coord2D &position) const {
	if (chunks.count(position) == 1)
		return chunks[position];

	return nullptr;
}

bool map::WorldMap::loadChunk(const coord2D &position) const {
	const_cast<WorldMap *>(this)->genChunk(position);
	return false;
}

void map::WorldMap::setChunk(map::Chunk *chunk) {
	chunks[chunk->getPosition()] = chunk;
}

map::Chunk *map::WorldMap::genChunk(const coord2D &coord) {
	auto chunk = chunks[coord] = new Chunk(this, coord);
	chunkGenerator.fillChunk(chunk);
	return chunk;
}
