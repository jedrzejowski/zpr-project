//
// Created by adam on 15.10.2019.
//

#include "block.h"


void block::Block::setPosition(map::Chunk *chunk, const block::position &pos) {
	this->pos = pos;
	this->chunk = chunk;
}
