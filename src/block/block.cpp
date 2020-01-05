#include "block.h"
#include "src/map/Map.h"

block::Block::Block() {
}

void block::Block::setPosition(map::Chunk *chunk, const Coord3D &pos) {
	this->position = pos;
	this->chunk = chunk;
}

block::Block *block::Block::getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const {
	auto targetChunk = this->chunk;

	CoordDim x = position.x + dx,
			y = position.y + dy,
			z = position.z + dz;

	if (z != std::clamp(z, (CoordDim) 0, map::Chunk::Size.y - 1)) return nullptr;

	while (x < 0) {
		targetChunk = targetChunk->getNeighbor(-1, 0).operator->();
		x += map::Chunk::Size.x;

		if (targetChunk == nullptr) return nullptr;
	}

	while (x >= map::Chunk::Size.x) {
		targetChunk = targetChunk->getNeighbor(+1, 0).operator->();
		x -= map::Chunk::Size.x;

		if (targetChunk == nullptr) return nullptr;
	}

	while (y < 0) {
		targetChunk = targetChunk->getNeighbor(0, -1).operator->();
		y += map::Chunk::Size.y;

		if (targetChunk == nullptr) return nullptr;
	}

	while (y >= map::Chunk::Size.y) {
		targetChunk = targetChunk->getNeighbor(0, +1).operator->();
		y -= map::Chunk::Size.y;

		if (targetChunk == nullptr) return nullptr;
	}

	return targetChunk->getBlock(Coord3D(x, y, z));
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
