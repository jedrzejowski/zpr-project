#pragma once

#include "src/_classdef.h"
#include <src/lib/perlin.h>

namespace map {
	class ChunkGenerator {
	private:
		PerlinNoise noise;
	public:
		explicit ChunkGenerator();

		void fillChunk(Chunk *chunk);
	};
}
