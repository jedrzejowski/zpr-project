#pragma once


#include "src/gengine/gEngine.h"
#include "_classdef.h"

namespace map {

	class ChunkRenderer : public gengine::Abs3DObj {
	private:
		Chunk *chunk;
	public:
		ChunkRenderer(Chunk *chunk);

		void render(gengine::Scene *scene) override;
	};
}