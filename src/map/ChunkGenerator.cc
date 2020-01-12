/**
 * @file ChunkGenerator.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "ChunkGenerator.h"
#include "Chunk.h"
#include "World.h"
#include "boost/random.hpp"
#include <bits/stdc++.h>


boost::mt19937 rng;
boost::uniform_int<> seedGen(26849 - 100, 26849 + 100);

map::ChunkGenerator::ChunkGenerator(World *world) {
	this->world = world;
	noise.set(1, 0.03, 4, 3, 26849);

	noise.set(
			1,
			0.03,
			double(Chunk::Size.z) / 8,
			3,
			seedGen(rng)
	);
}

void map::ChunkGenerator::fillChunk(ChunkPtr &chunk) {

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
}


//region SavableObject

const char *JSON_ATTR_PERSISTENCE = "persistence";
const char *JSON_ATTR_FREQUENCY = "frequency";
const char *JSON_ATTR_AMPLITUDE = "amplitude";
const char *JSON_ATTR_OCTAVES = "octaves";
const char *JSON_ATTR_RANDOMSEED = "randomseed";

boost::filesystem::path map::ChunkGenerator::getSavePath(AppSettings &app_settings) const {
	return world->getDirectory() / "seed";
}

json map::ChunkGenerator::toJSON() const {
	json json_obj;

	json_obj[JSON_ATTR_PERSISTENCE] = noise.getPersistence();
	json_obj[JSON_ATTR_FREQUENCY] = noise.getFrequency();
	json_obj[JSON_ATTR_AMPLITUDE] = noise.getAmplitude();
	json_obj[JSON_ATTR_OCTAVES] = noise.getOctaves();
	json_obj[JSON_ATTR_RANDOMSEED] = noise.getRandomSeed();

	return json_obj;
}

void map::ChunkGenerator::acceptState(json &json_obj) {

	noise.setPersistence(assertGetNumber(json_obj[JSON_ATTR_PERSISTENCE]));
	noise.setFrequency(assertGetNumber(json_obj[JSON_ATTR_FREQUENCY]));
	noise.setAmplitude(assertGetNumber(json_obj[JSON_ATTR_AMPLITUDE]));
	noise.setOctaves(assertGetNumber(json_obj[JSON_ATTR_OCTAVES]));
	noise.setRandomSeed(assertGetNumber(json_obj[JSON_ATTR_RANDOMSEED]));
}

//endregion
