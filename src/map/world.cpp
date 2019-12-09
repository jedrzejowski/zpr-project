#include "world.h"
#include "chunk.h"

map::World::World() {

	chunkLoader = new ChunkLoader(this);
}

bool map::World::hasChunk(const Coord2D &position) {
	return chunks.count(position) == 1;
}

map::ChunkPtr map::World::getChunk(const Coord2D &position) {
	if (hasChunk(position))
		return chunks[position];

	return nullptr;
}

void map::World::requestChunk(Coord2D position) {
	chunkLoader->load(position);
}


void map::World::syncChunkWithLoader() {
	chunkLoader->syncWithWorld();
}

void map::World::insertChunk(map::ChunkPtr chunk) {
	if (hasChunk(chunk->getPosition()))
		throw zprException("inserting chunk which position already exist");

	chunks[chunk->getPosition()] = chunk;
	onChunkInserted(chunk);
}

map::ChunkPtr map::World::ejectChunk(const Coord2D &position) {
	if (!hasChunk(position))
		throw zprException("ejecting chunk not inserted chunk");

	auto chunk = chunks[position];
	chunks.erase(position);

	onChunkEjected(chunk);

	return chunk;
}
