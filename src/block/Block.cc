/**
 * @file Block.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Block.h"
#include "src/map/Map.h"

const block::BlockWPtr block::Air = block::BlockWPtr();

block::Block::Block(json &data) {
}

void block::Block::setPosition(map::ChunkPtr &chunk_ptr, const Coord3D &pos) {
	this->position = pos;
	this->chunk = chunk_ptr;
}

block::BlockWPtr block::Block::getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const {
	if (auto targetChunk = this->chunk.lock()) {

		CoordDim x = position.x + dx,
				y = position.y + dy,
				z = position.z + dz;

		if (z != std::clamp(z, CoordDim(0), CoordDim(map::Chunk::Size.z - 1))) return block::Air;

		while (x < 0) {
			targetChunk = targetChunk->getNeighbor(-1, 0).lock();

			if (targetChunk) {
				x += map::Chunk::Size.x;
			} else return block::Air;
		}

		while (x >= map::Chunk::Size.x) {
			targetChunk = targetChunk->getNeighbor(+1, 0).lock();

			if (targetChunk) {
				x -= map::Chunk::Size.x;
			} else return block::Air;
		}

		while (y < 0) {
			targetChunk = targetChunk->getNeighbor(0, -1).lock();

			if (targetChunk) {
				y += map::Chunk::Size.y;
			} else return block::Air;
		}

		while (y >= map::Chunk::Size.y) {
			targetChunk = targetChunk->getNeighbor(0, +1).lock();

			if (targetChunk) {
				y -= map::Chunk::Size.y;
			} else return block::Air;
		}

		auto pos = Coord3D(x, y, z);

		return targetChunk->isAir(pos) ? block::Air : targetChunk->getBlock(pos);
	} else {
		return block::Air;
	}
}

bool block::Block::isSolid() {
	return false;
}

json block::Block::toJSON() {
	json j;

	j[JSON_ATTR_TYPE_ID] = typeId();

	return j;
}


engine::SquareTextureReference block::getBlockTexture(int x, int y) {
	return engine::SquareTextureReference(
			glm::vec2((float(x) - 1) / global::TextureBlocksColumns, (float(y) - 1) / global::TextureBlocksRows),
			glm::vec2(float(x) / global::TextureBlocksColumns, float(y) / global::TextureBlocksRows),
			global::TextureBlocksNo
	);
}