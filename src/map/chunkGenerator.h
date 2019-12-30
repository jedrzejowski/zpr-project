#pragma once

#include "src/_classdef.h"
#include "src/lib/perlin.h"
#include "src/lib/coord.h"

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
