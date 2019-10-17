#pragma once

#include "src/types.h"
#include "_classdef.h"
#include "src/map/Map.h"

namespace block {
	class Block {
	private:
		map::Chunk* chunk;
		position pos;

	public:

		void setPosition(map::Chunk* chunk, const position &pos);
	};
}

