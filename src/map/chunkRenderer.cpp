#include "chunkRenderer.h"
#include "renderer.h"
#include "chunk.h"

map::ChunkRenderer::ChunkRenderer(map::Renderer *renderer, Chunk *chunk)
		: Object(renderer) {
	this->renderer = renderer;
	this->chunk = chunk;

	initVerticles();
}

void map::ChunkRenderer::initVerticles() {
	this->visibleBlocks = chunk->getAllBlocks();

	auto coord = chunk->getPosition();
	chunkPos = glm::translate(glm::mat4(1),
							  glm::vec3(
									  coord.x * Chunk::Size.x,
									  coord.y * Chunk::Size.y,
									  0
							  ));

	for (auto iter : visibleBlocks) {
		auto block = iter.second;
		block->insertToBuffers(vertices, indices);
	}

	iChangedBuffers();
	insertToBuffers();
}

void map::ChunkRenderer::render(engine::Scene *scene) {
	renderer->getShader()->setMat4("chunkPos", chunkPos);
	draw();
}

