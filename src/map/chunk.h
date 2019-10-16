#pragma once

#include "src/types.h"
#include "src/gengine/gEngine.h"

namespace map {
	class Chunk : public gengine::Abs3DObj {
	protected:
		gengine::Texture *stoneTex;
	public:
		Chunk();
		static ushort MAX_X, MAX_Y, MAX_Z;

		void render(gengine::Window *window) override;
	};
}

