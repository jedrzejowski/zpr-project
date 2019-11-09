#include "chunkRenderer.h"
#include "worldRenderer.h"
#include "chunk.h"

map::ChunkRenderer::ChunkRenderer(map::WorldRenderer *renderer, Chunk *chunk)
		: Object(renderer) {
	this->renderer = renderer;
	this->chunk = chunk;

}

void map::ChunkRenderer::updateBuffers() {
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
		block->insertToBuffers(verticesBuf, indicesBuf);
	}
}

void map::ChunkRenderer::render(const engine::Scene *scene) {
	renderer->getShader()->setMat4("chunkPos", chunkPos);
	draw();
}

