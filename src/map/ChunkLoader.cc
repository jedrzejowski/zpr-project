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
		auto worldMapPtr = world->shared_from_this();
		auto chunk = map::Chunk::create(worldMapPtr, coord);


		if (chunk->hasSavedFile())

			try {

				chunk->loadObjectFromFile();
			} catch (WrongJsonException &exception) {

				logger(0).err("Error during parsing chunk data.").err("I will generate new one");

				world->chunkGenerator.fillChunk(chunk);
			} catch (FileInputException &exception) {

				logger(0).err("Error during reading chunk from file:").enter()
						.err(exception.getFile()).enter()
						.err("I will generate new one");

				world->chunkGenerator.fillChunk(chunk);
			}

		else {
			world->chunkGenerator.fillChunk(chunk);

			try {

				chunk->saveObjectToFile();
			} catch (FileOutputException &exception) {

				logger(0).err("Error during chunk saving to file.");
			}
		}


		std::lock_guard<std::mutex> lock(chunkListAccess);
		chunksToAdd.push_back(chunk);
	});
}

void map::ChunkLoader::unload(Coord2D coord) {
	if (!isChunkLoaded(coord)) return;

	chunksToRemove.push_back(coord);
}

map::ChunkLoader::~ChunkLoader() {
}

void map::ChunkLoader::syncWithWorld() {
	std::lock_guard<std::mutex> lock(chunkListAccess);

	if (chunksToAdd.empty() && chunksToRemove.empty()) return;


	while (!chunksToAdd.empty()) {
		auto chunk = chunksToAdd.front();
		chunksToAdd.pop_front();

		world->insertChunk(chunk);
	}

	while (!chunksToRemove.empty()) {
		auto pos = chunksToRemove.front();
		chunksToRemove.pop_front();

		auto chunk = world->ejectChunk(pos);

		worker.push([this, chunk] {

			chunk->saveObjectToFile();

			std::lock_guard<std::mutex> lock(chunkListAccess);
			unloadingChunksCoords.remove(chunk->getPosition());
		});
	}
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