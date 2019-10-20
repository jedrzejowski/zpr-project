#include "src/logger.h"
#include "chunk.h"

map::Chunk::Chunk() {

	addBlock(block::position(0, 0, 0), new block::Block());
}


block::Block *map::Chunk::getBlock(const block::position &position) {
	return blocks[position];
}

bool map::Chunk::addBlock(const block::position &position, block::Block *block) {
	block->setPosition(this, position);
	blocks[position] = block;
	return false;
}

std::map<block::position, block::Block *> map::Chunk::getAllBlocks() {
	return blocks;
}

std::map<block::position, block::Block *> map::Chunk::getVisibleBlocks() {
	return blocks;
}
