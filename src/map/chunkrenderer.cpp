#include <src/logger.h>
#include "chunkrenderer.h"

#include "chunk.h"

map::ChunkRenderer::ChunkRenderer(Chunk *chunk) {
	this->chunk = chunk;
	initVerticles();
}

void map::ChunkRenderer::initVerticles() {
	this->visibleBlocks = chunk->getAllBlocks();
	Logger::get().log(std::to_string(visibleBlocks.size()));

	for (auto iter : visibleBlocks) {
		auto block = iter.second;
		block->insertToBuffers(vertices, indices);
		Logger::get().log(std::to_string(vertices.size()));
	}


	insertObjToBuffers();
}

void map::ChunkRenderer::render(engine::Scene *scene) {
	draw();
}

