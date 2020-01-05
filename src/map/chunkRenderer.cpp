#include "chunkRenderer.h"
#include "worldRenderer.h"
#include "chunk.h"
#include "worldShader.h"

map::ChunkRenderer::ChunkRenderer(map::WorldRenderer *renderer, map::ChunkPtr chunk) : Abs3DObj() {
	logger.constructor(this);
	this->worldRenderer = renderer;
	this->chunk = chunk;
}


map::ChunkRenderer::~ChunkRenderer() {
	logger.destructor(this);
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

	setNeedRefreshBuffers(false);
}

void map::ChunkRenderer::render(const engine::ScenePtr scene) {
	worldRenderer->getShader()->setChunkPos(chunkPos);
	drawTriangles();
}

