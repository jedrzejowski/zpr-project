//
// Created by adam on 08.11.2019.
//

#include "chunkLoader.h"
#include "chunk.h"
#include "worldRenderer.h"
#include "chunkRenderer.h"

map::ChunkLoader::ChunkLoader(map::World *world) :
		world(world),
		Object(world) {
}

void map::ChunkLoader::load(Coord2D coord) {
	if (isChunkUnloading(coord)) return;
	if (isChunkLoading(coord)) return;

	loadingChunksCoords.push_back(coord);

	worker.push([this, coord] {
		auto chunk = generateNewChunk(coord);

		chunkListAccess.lock();
		chunksToAdd.push_back(chunk);
		chunkListAccess.unlock();
	});
}

void map::ChunkLoader::unload(Coord2D coord) {
//	if (isChunkUnloading(coord)) return;
//	if (!isChunkLoaded(coord)) return;
}

map::ChunkLoader::~ChunkLoader() {
}

void map::ChunkLoader::syncWithWorld() {
	if (chunksToAdd.empty() && chunksToRemove.empty()) return;
	chunkListAccess.lock();
	if (chunksToAdd.empty() && chunksToRemove.empty()) {
		chunkListAccess.unlock();
		return;
	}

	while (!chunksToAdd.empty()) {
		auto chunk = chunksToAdd.back();
		chunksToAdd.pop_back();

		world->insertChunk(chunk);
	}

//	while (!chunksToRemove.empty()) {
//		auto chunk = chunksToRemove.back();
//		chunksToRemove.pop_back();
//
//		world->ejectChunk(chunk->getPosition());
//	}

	chunkListAccess.unlock();
}

bool map::ChunkLoader::isChunkLoaded(const Coord2D &coord) {
	auto chunk = world->getChunk(coord);
	return chunk == nullptr;
}

bool map::ChunkLoader::isChunkLoading(const Coord2D &coord) {
	return std::find(loadingChunksCoords.begin(), loadingChunksCoords.end(), coord) != loadingChunksCoords.end();
}

bool map::ChunkLoader::isChunkUnloading(const Coord2D &coord) {
	return std::find(unloadingChunksCoords.begin(), unloadingChunksCoords.end(), coord) != unloadingChunksCoords.end();;
}

map::Chunk *map::ChunkLoader::generateNewChunk(const Coord2D &coord) {
	auto chunk = new Chunk(world, coord);
	chunkGenerator.fillChunk(chunk);
	return chunk;
}

map::Chunk *map::ChunkLoader::readChunkFromFile(const Coord2D &coord) {
	return generateNewChunk(coord);
}
