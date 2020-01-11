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

	loading_chunks_coords.push_back(coord);

	worker.push([this, coord] {
		auto worldMapPtr = world->shared_from_this();
		auto chunk = map::Chunk::create(worldMapPtr, coord);

		auto genChunk = [&] {
			world->chunk_generator.fillChunk(chunk);

			try {
				chunk->saveObjectToFile();
			} catch (FileOutputException &exception) {
				logger(0).err("Error occured while saving chunk to file:").enter().log(exception.getFile());
			}
		};

		if (chunk->hasSavedFile())
			chunk->loadObjectFromFile(genChunk);
		else genChunk();


		std::lock_guard<std::mutex> lock(chunk_list_access);
		chunks_to_add.push_back(chunk);
	});
}

void map::ChunkLoader::unload(Coord2D coord) {
	if (!isChunkLoaded(coord)) return;

	chunks_to_remove.push_back(coord);
}

map::ChunkLoader::~ChunkLoader() {
}

void map::ChunkLoader::syncWithWorld() {
	std::lock_guard<std::mutex> lock(chunk_list_access);

	if (chunks_to_add.empty() && chunks_to_remove.empty()) return;


	while (!chunks_to_add.empty()) {
		auto chunk = chunks_to_add.front();
		chunks_to_add.pop_front();

		world->insertChunk(chunk);
	}

	while (!chunks_to_remove.empty()) {
		auto pos = chunks_to_remove.front();
		chunks_to_remove.pop_front();

		auto chunk = world->ejectChunk(pos);

		worker.push([this, chunk] {

			chunk->saveObjectToFile();

			std::lock_guard<std::mutex> lock(chunk_list_access);
			unloading_chunks_coords.remove(chunk->getPosition());
		});
	}
}

bool map::ChunkLoader::isChunkLoaded(const Coord2D &coord) {
	return world->chunks.count(coord) == 1;
}

bool map::ChunkLoader::isChunkLoading(const Coord2D &coord) {
	return std::find(loading_chunks_coords.begin(), loading_chunks_coords.end(), coord) != loading_chunks_coords.end();
}

bool map::ChunkLoader::isChunkUnloading(const Coord2D &coord) {
	return std::find(unloading_chunks_coords.begin(), unloading_chunks_coords.end(), coord) !=
		   unloading_chunks_coords.end();;
}