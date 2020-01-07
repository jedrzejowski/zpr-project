/**
 * @file ChunkLoader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "ChunkLoader.h"
#include "Chunk.h"
#include "WorldRenderer.h"
#include "ChunkRenderer.h"
#include "World.h"

map::ChunkLoader::ChunkLoader(World *world) :
		world(world) {
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
	if (!isChunkLoaded(coord)) return;

	chunksToRemove.push_back(coord);
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

	while (!chunksToRemove.empty()) {
		auto pos = chunksToRemove.back();
		chunksToRemove.pop_back();

		auto chunk = world->ejectChunk(pos);

		worker.push([this, chunk] {

			chunk->save();

			chunkListAccess.lock();
			unloadingChunksCoords.remove(chunk->getPosition());
			chunkListAccess.unlock();
		});
	}

	chunkListAccess.unlock();
}

bool map::ChunkLoader::isChunkLoaded(const Coord2D &coord) {
	return world->chunks.count(coord) == 1;
}

bool map::ChunkLoader::isChunkLoading(const Coord2D &coord) {
	return std::find(loadingChunksCoords.begin(), loadingChunksCoords.end(), coord) != loadingChunksCoords.end();
}

bool map::ChunkLoader::isChunkUnloading(const Coord2D &coord) {
	return std::find(unloadingChunksCoords.begin(), unloadingChunksCoords.end(), coord) != unloadingChunksCoords.end();;
}

map::ChunkPtr map::ChunkLoader::generateNewChunk(const Coord2D &coord) {
	return world->chunkGenerator.newVirginChunk(coord);
}

map::ChunkPtr map::ChunkLoader::readChunkFromFile(const Coord2D &coord) {
	return generateNewChunk(coord);
}
