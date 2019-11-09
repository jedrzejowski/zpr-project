#include "world.h"
#include "chunk.h"

map::World::World() {

	chunkLoader = new ChunkLoader(this);
}

map::Chunk *map::World::getChunk(Coord2D position) {
	if (chunks.count(position) == 1)
		return chunks[position];

	return nullptr;
}

void map::World::requestChunk(Coord2D position) {
	chunkLoader->load(position);
}

void map::World::setChunk(map::Chunk *chunk) {
	chunks[chunk->getPosition()] = chunk;
}

void map::World::syncChunkWithLoader() {
	chunkLoader->syncWithWorld();
}

//map::Chunk *map::World::genChunk(const Coord2D &coord) {
//	auto chunk = chunks[coord] = new Chunk(this, coord);
//	chunkGenerator.fillChunk(chunk);
//	return chunk;
//}
