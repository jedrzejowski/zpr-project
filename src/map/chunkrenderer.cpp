#include <src/logger.h>
#include "chunkrenderer.h"

#include "chunk.h"

map::ChunkRenderer::ChunkRenderer(Chunk *chunk) {
	this->chunk = chunk;
	initVerticles();
}

void map::ChunkRenderer::initVerticles() {
	this->visibleBlocks = chunk->getAllBlocks();

	for (auto iter : visibleBlocks) {
		auto block = iter.second;
		block->insertToBuffers(vertices, indices);
	}

	insertObjToBuffers();
}

void map::ChunkRenderer::render(engine::Scene *scene) {
	draw();
}

