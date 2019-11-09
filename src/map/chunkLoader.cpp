//
// Created by adam on 08.11.2019.
//

#include "chunkLoader.h"

map::ChunkLoader::ChunkLoader(map::World *world) :
		world(world),
		Object(world) {
}

void map::ChunkLoader::load(Coord2D coord) {
	logger.log(coord);
}

void map::ChunkLoader::unload(Coord2D coord) {
}

map::ChunkLoader::~ChunkLoader() {
}

void map::ChunkLoader::syncWithWorld() {

}
