//
// Created by adam on 15.10.2019.
//

#include "block.h"

block::Block::Block() {
}

void block::Block::setPosition(map::Chunk *chunk, const block::cord3D &pos) {
	this->position = pos;
	this->chunk = chunk;
}
