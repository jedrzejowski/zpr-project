/**
 * @file ChunkGenerator.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "ChunkGenerator.h"
#include "Chunk.h"
#include "World.h"

map::ChunkGenerator::ChunkGenerator(World *world) {
	this->world = world;
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

map::ChunkPtr map::ChunkGenerator::newVirginChunk(const Coord2D &position) {
	auto worldMapPtr = world->shared_from_this();
	auto chunk = map::Chunk::create(worldMapPtr, position);

	block::BlockPtr block;

	for (CoordDim x = 0; x < Chunk::Size.x; x++) {
		for (CoordDim y = 0; y < Chunk::Size.y; y++) {

			CoordDim z = noise.getHeight(
					x + chunk->position.x * Chunk::Size.x,
					y + chunk->position.y * Chunk::Size.y
			) + (Chunk::Size.z / 2);

			z = std::clamp(z, (CoordDim) 0, Chunk::Size.z - 1);

			int dirtLeft = 3;

			for (auto i = z; i >= 0; i--) {

				if (i == z) {
					block = std::make_shared<block::Grass>();
					dirtLeft--;
				} else if (dirtLeft > 0) {
					block = std::make_shared<block::Dirt>();
					dirtLeft--;
				} else {
					block = std::make_shared<block::Stone>();
				}

				chunk->setBlock(Coord3D(x, y, i), block);
			}
		}
	}

	return chunk;
}