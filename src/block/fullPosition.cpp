//
// Created by adam on 05.01.2020.
//

#include "fullPosition.h"
#include "src/map/chunk.h"


block::FullPosition::FullPosition() {
}

block::FullPosition::FullPosition(const Coord2D &chunk, const Coord3D &block) : chunk(chunk), block(block) {}

block::FullPosition block::FullPosition::getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const {

	FullPosition position = *this;

	position.block.x += dx;
	position.block.y += dy;
	position.block.z += dz;

	while (position.block.x < 0) {
		position.chunk.x -= 1;
		position.block.x += map::Chunk::Size.x;
	}

	while (position.block.x >= map::Chunk::Size.x) {
		position.chunk.x += 1;
		position.block.x -= map::Chunk::Size.x;
	}

	while (position.block.y < 0) {
		position.chunk.y -= 1;
		position.block.y += map::Chunk::Size.y;
	}

	while (position.block.y >= map::Chunk::Size.y) {
		position.chunk.y += 1;
		position.block.y -= map::Chunk::Size.y;
	}

	return position;
}

const Coord2D &block::FullPosition::getChunk() const {
	return chunk;
}

void block::FullPosition::setChunk(const Coord2D &chunk) {
	FullPosition::chunk = chunk;
}

const Coord3D &block::FullPosition::getBlock() const {
	return block;
}

void block::FullPosition::setBlock(const Coord3D &block) {
	FullPosition::block = block;
}

bool block::FullPosition::isValid() {
	return 0 <= block.x && block.x < map::Chunk::Size.x &&
		   0 <= block.y && block.y < map::Chunk::Size.y &&
		   0 <= block.z && block.z < map::Chunk::Size.z;
}

glm::vec3 block::FullPosition::toVec() const {
	return glm::vec3(
			map::Chunk::Size.x * chunk.x + block.x,
			map::Chunk::Size.x * chunk.y + block.y,
			block.z
	);
}

