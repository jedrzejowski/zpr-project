#pragma once

#include "src/_classdef.h"
#include "src/lib/perlin.h"
#include "src/lib/coord.h"

namespace map {
	class ChunkGenerator {
	private:
		PerlinNoise noise;
	public:
		explicit ChunkGenerator();

		map::ChunkPtr newVirginChunk(World *worldMap, const Coord2D &position);
	};
}
