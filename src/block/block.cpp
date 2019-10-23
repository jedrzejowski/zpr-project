#include "block.h"
#include "src/func/clip.h"
#include "src/map/Map.h"

block::Block::Block() {
}

void block::Block::setPosition(map::Chunk *chunk, const coord3D &pos) {
	this->position = pos;
	this->chunk = chunk;
}

block::Block *block::Block::getNeighbor(int64_t dx, int64_t dy, int64_t dz) const {
	auto targetChunk = this->chunk;

	int64_t x = position.x + dx,
			y = position.y + dy,
			z = position.z + dz;

	if (z != clip((int64_t) 0, z, map::Chunk::Size.y - 1)) return nullptr;

	while (x < 0) {
		targetChunk = targetChunk->getNeighbor(-1, 0);
		x += map::Chunk::Size.x;

		if (targetChunk == nullptr) return nullptr;
	}

	while (x >= map::Chunk::Size.x) {
		targetChunk = targetChunk->getNeighbor(+1, 0);
		x -= map::Chunk::Size.x;

		if (targetChunk == nullptr) return nullptr;
	}

	while (y < 0) {
		targetChunk = targetChunk->getNeighbor(0, -1);
		y += map::Chunk::Size.y;

		if (targetChunk == nullptr) return nullptr;
	}

	while (y >= map::Chunk::Size.y) {
		targetChunk = targetChunk->getNeighbor(0, +1);
		y -= map::Chunk::Size.y;

		if (targetChunk == nullptr) return nullptr;
	}

	return targetChunk->getBlock(coord3D(x, y, z));
}

bool block::Block::isSolid() {
	return false;
}
