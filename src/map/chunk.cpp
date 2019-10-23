#include "chunk.h"

const coord3D map::Chunk::Size = coord3D(16, 16, 16);

map::Chunk::Chunk(const coord2D &position) :
		position(position) {

//	addBlock(coord3D(0, 0, 0), new block::Stone());
//	addBlock(coord3D(1, 0, 0), new block::Stone());
//	addBlock(coord3D(0, 1, 0), new block::Stone());

}


block::Block *map::Chunk::getBlock(const coord3D &position) {
	return blocks[position];
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
