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

	CoordDim sandWaterOffset = 3;
	CoordDim dirtOffset = 3;

	CoordDim waterLevel = Chunk::Size.z / 2;

	for (CoordDim x = 0; x < Chunk::Size.x; x++) {
		for (CoordDim y = 0; y < Chunk::Size.y; y++) {

			CoordDim z = noise.getHeight(
					x + chunk->position.x * Chunk::Size.x,
					y + chunk->position.y * Chunk::Size.y
			) + waterLevel;

			z = std::clamp(z, (CoordDim) 0, Chunk::Size.z - 1);

			auto is_water_near = false;
			for (CoordDim x2 = -sandWaterOffset; x2 < x + sandWaterOffset; x2++)
				for (CoordDim y2 = -sandWaterOffset; y2 <= y + sandWaterOffset; y2++)
					if (z <= waterLevel) {
						is_water_near = true;
						goto waterEnd;
					}
			waterEnd:

			auto dirt_left = dirtOffset;

			// wypełnienie wodą
			for (auto i = waterLevel; i > z; i--) {
				block = std::make_shared<block::Water>();
				chunk->setBlock(Coord3D(x, y, i), block);
			}

			for (auto i = z; i >= 0; i--) {

				if (dirt_left > 0) {
					if (is_water_near) block = std::make_shared<block::Sand>();
					else {
						if (i == z) block = std::make_shared<block::Grass>();
						else block = std::make_shared<block::Dirt>();
					}

					dirt_left--;
				} else {
					block = std::make_shared<block::Stone>();
				}

				chunk->setBlock(Coord3D(x, y, i), block);
			}
		}
	}

	return chunk;
}