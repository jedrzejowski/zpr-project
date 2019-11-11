#include "chunk.h"
#include "world.h"

const Coord3D map::Chunk::Size = Coord3D(16, 16, 16);

map::Chunk::Chunk(World *worldMap, const Coord2D &position) :
		Object(worldMap),
		worldMap(worldMap),
		position(position) {
}


block::Block *map::Chunk::getBlock(const Coord3D &position) {
	if (blocks.count(position) == 1)
		return blocks[position];
	return nullptr;
}

bool map::Chunk::setBlock(const Coord3D &position, block::Block *block) {
	block->setPosition(this, position);

	blocks[position] = block;
	return false;
}

std::map<Coord3D, block::Block *> map::Chunk::getAllBlocks() {
	return blocks;
}

const Coord2D &map::Chunk::getPosition() const {
	return position;
}

map::Chunk *map::Chunk::getNeighbor(CoordDim dx, CoordDim dy) const {
	auto neighborPos = position;
	neighborPos.x += dx;
	neighborPos.y += dy;
	return worldMap->getChunk(neighborPos);
}
