#include "chunk.h"

map::Chunk::Chunk() {

	addBlock(cord3D(0, 0, 0), new block::Stone());
	addBlock(cord3D(1, 0, 0), new block::Stone());
	addBlock(cord3D(0, 1, 0), new block::Stone());
}


block::Block *map::Chunk::getBlock(const cord3D &position) {
	return blocks[position];
}

bool map::Chunk::addBlock(const cord3D &position, block::Block *block) {
	block->setPosition(this, position);

	blocks[position] = block;
	return false;
}

std::map<cord3D, block::Block *> map::Chunk::getAllBlocks() {
	return blocks;
}