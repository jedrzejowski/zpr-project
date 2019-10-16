//
// Created by adam on 15.10.2019.
//

#include "worldmap.h"

map::WorldMap::WorldMap() {
}

map::Chunk *map::WorldMap::getChunk(int x, int y) {
	auto pos = ChunkPos(x, y);
	if (chunks.count(pos) == 1)
		return chunks[pos];
	return nullptr;
}

map::Chunk *map::WorldMap::genChunk(int x, int y) {
	return nullptr;
}

bool map::WorldMap::loadChunk(int x, int y) {
	return false;
}

void map::WorldMap::setChunk(int x, int y, map::Chunk *chunk) {
	chunks[ChunkPos(x, y)] = chunk;
}
