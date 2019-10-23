//
// Created by adam on 23.10.2019.
//

#include <src/func/clip.h>
#include "chunkGenerator.h"
#include "chunk.h"

map::ChunkGenerator::ChunkGenerator() {
	noise.set(1, 1, 2, 1, 0);
}

void map::ChunkGenerator::fillChunk(map::Chunk *chunk) {
	for (int64_t x = 0; x < Chunk::Size.x; x++) {
		for (int64_t y = 0; y < Chunk::Size.y; y++) {

			int64_t z = noise.getHeight(x, y) + Chunk::Size.z / 2;
			z = clip((int64_t) 0, z, Chunk::Size.z - 1);

			for (; z >= 0; z--) {
				chunk->addBlock(coord3D(x, y, z), new block::Stone());
			}
		}
	}
}
