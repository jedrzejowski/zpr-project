#include "block.h"
#include "src/map/Map.h"

const block::BlockWPtr block::Air = block::BlockWPtr();

block::Block::Block() {
//	logger.constructor(this);
}
block::Block::~Block() {
//	logger.destructor(this);
}


void block::Block::setPosition(map::ChunkPtr &chunkPtr, const Coord3D &pos) {
	this->position = pos;
	this->chunk = chunkPtr;
}

block::BlockWPtr block::Block::getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const {
	auto targetChunk = this->chunk;

	CoordDim x = position.x + dx,
			y = position.y + dy,
			z = position.z + dz;

	if (z != std::clamp(z, (CoordDim) 0, map::Chunk::Size.y - 1)) return block::Air;

	while (x < 0) {
		targetChunk = targetChunk.lock()->getNeighbor(-1, 0);
		x += map::Chunk::Size.x;

		if (targetChunk.expired()) return block::Air;
	}

	while (x >= map::Chunk::Size.x) {
		targetChunk = targetChunk.lock()->getNeighbor(+1, 0);
		x -= map::Chunk::Size.x;

		if (targetChunk.expired()) return block::Air;
	}

	while (y < 0) {
		targetChunk = targetChunk.lock()->getNeighbor(0, -1);
		y += map::Chunk::Size.y;

		if (targetChunk.expired()) return block::Air;
	}

	while (y >= map::Chunk::Size.y) {
		targetChunk = targetChunk.lock()->getNeighbor(0, +1);
		y -= map::Chunk::Size.y;

		if (targetChunk.expired()) return block::Air;
	}

	return targetChunk.lock()->getBlock(Coord3D(x, y, z));
}

bool block::Block::isSolid() {
	return false;
}

json block::Block::toJSON() {
	json j;

	j["typeId"] = typeId();

	return j;
}

const float block::Block::TexColumns = 3;
const float block::Block::TexRows = 4;

std::tuple<glm::vec2, glm::vec2> block::Block::getBlockText(int x, int y) {
	return {
			glm::vec2((float(x) - 1) / TexColumns, (float(y) - 1) / TexRows),
			glm::vec2(float(x) / TexColumns, float(y) / TexRows)
	};
}