#pragma once

#include "src/_classdef.h"
#include "src/lib/PerlinNoise.h"
#include "src/lib/Coord.hpp"

namespace map {
	class ChunkGenerator {
	private:
		PerlinNoise noise;
		World* world;
	public:
		explicit ChunkGenerator(World* world);

		map::ChunkPtr newVirginChunk(const Coord2D &position);
	};
}
