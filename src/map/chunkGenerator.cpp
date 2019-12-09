//
// Created by adam on 23.10.2019.
//

#include "chunkGenerator.h"
#include "chunk.h"

map::ChunkGenerator::ChunkGenerator() {
	noise.set(1, 0.03, 4, 3, 26849);

//	lenght=8192
//	width=8192
//	amplitude=200
//	frequency=0.03
//	octaves=3
//	persistence=1
//	randomseed=26849
//	lowgraphic=false

}

map::ChunkPtr map::ChunkGenerator::newVirginChunk(map::World *worldMap, const Coord2D &position) {
	auto chunk = std::make_shared<map::Chunk>(worldMap, position);

	for (CoordDim x = 0; x < Chunk::Size.x; x++) {
		for (CoordDim y = 0; y < Chunk::Size.y; y++) {

			CoordDim z = noise.getHeight(
					x + chunk->position.x * Chunk::Size.x,
					y + chunk->position.y * Chunk::Size.y
			) + (Chunk::Size.z / 2);

			z = std::clamp(z, (CoordDim) 0, Chunk::Size.z - 1);

			int dirtLeft = 3;

			for (; z >= 0; z--) {
				if (dirtLeft > 0) {

					chunk->setBlock(Coord3D(x, y, z), new block::Dirt());
					dirtLeft--;
				} else {
					chunk->setBlock(Coord3D(x, y, z), new block::Stone());
				}
			}
		}
	}
}