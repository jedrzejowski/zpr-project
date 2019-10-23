#include "chunk.h"

const coord3D map::Chunk::Size = coord3D(16, 16, 16);

map::Chunk::Chunk(WorldMap *worldMap, const coord2D &position) :
		Object(worldMap),
		worldMap(worldMap),
		position(position) {
}


block::Block *map::Chunk::getBlock(const coord3D &position) {
	if (blocks.count(position) == 1)
		return blocks[position];
	return nullptr;
}

bool map::Chunk::addBlock(const coord3D &position, block::Block *block) {
	block->setPosition(this, position);

	blocks[position] = block;
	return false;
}

std::map<coord3D, block::Block *> map::Chunk::getAllBlocks() {
	return blocks;
}

const coord2D &map::Chunk::getPosition() const {
	return position;
}

map::Chunk *map::Chunk::getNeighbor(int64_t dx, int64_t dy) const {
	auto neighborPos = position;
	neighborPos.x += dx;
	neighborPos.y += dy;
	return worldMap->getChunk(neighborPos);
}
