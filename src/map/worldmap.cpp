#include "worldmap.h"
#include "chunk.h"

map::WorldMap::WorldMap() {
}

map::Chunk *map::WorldMap::getChunk(const coord2D &position) const {
	if (chunks.count(position) == 1)
		return chunks[position];

	return chunks[position] = genChunk(position);
}

bool map::WorldMap::loadChunk(const coord2D &position) {
	return false;
}

void map::WorldMap::setChunk(map::Chunk *chunk) {
	chunks[chunk->getPosition()] = chunk;
}

map::Chunk *map::WorldMap::genChunk(const coord2D &coord) const {
	auto chunk = new Chunk(coord);
	chunkGenerator.fillChunk(chunk);
	return chunk;
}
