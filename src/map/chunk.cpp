#include "src/logger.h"
#include "chunk.h"

map::Chunk::Chunk() : Abs3DObj() {

	stoneTex = gengine::Resources::get().getTexture("texture/block/stone.png");

	addBlock(block::position(0, 0, 0), new block::Block());

	initVerticles();
	initIndicies();
	insertObjToBuffers();
}

void map::Chunk::render(gengine::Window *window) {
	Logger::get().info("render");
	stoneTex->use();
	draw();
}

void map::Chunk::initVerticles() {

	verticesNum = (map::Chunk::MAX_X + 1) * (map::Chunk::MAX_Y + 1) * (map::Chunk::MAX_Z + 1);
	vertices = new gengine::Point3DeX[verticesNum];

	for (ushort x = 0; x <= MAX_X; x++)
		for (ushort y = 0; y <= MAX_X; y++)
			for (ushort z = 0; z <= MAX_X; z++)
				vertices[getVerticleIndex(x, y, z)] = gengine::Point3DeX(x, y, z);
}

void map::Chunk::initIndicies() {
	indicesNum = 0;
	indicesVec.clear();

//	for (auto &iter: blocks)
//		block.
}


uint map::Chunk::getVerticleIndex(ushort x, ushort y, ushort z) {
	return x + y * (MAX_X + 1) + z * (MAX_X + 1) * (MAX_Y + 1);
}


block::Block *map::Chunk::getBlock(const block::position &position) {
	return blocks[position];
}

bool map::Chunk::addBlock(const block::position &position, block::Block *block) {
	block->setPosition(this, position);
	blocks[position] = block;
	return false;
}
