#include "src/_classdef.h"
#include <src/lib/perlin.h>

namespace map {
	class ChunkGenerator {
	private:
		PerlinNoise noise;
	public:
		ChunkGenerator();

		void fillChunk(Chunk* chunk);
	};
}
