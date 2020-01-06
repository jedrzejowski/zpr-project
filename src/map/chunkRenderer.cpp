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

	auto coord = chunk->getPosition();
	chunkPos = glm::translate(glm::mat4(1),
							  glm::vec3(
									  coord.x * Chunk::Size.x,
									  coord.y * Chunk::Size.y,
									  0
							  ));

	for (const auto& iter : chunk->getAllBlocks()) {
//		if()
		logger.log("stąd wyszedł SIGSEGV").log(iter.first).log(iter.second);
		iter.second->insertToBuffers(verticesBuf, indicesBuf);
	}

	setNeedRefreshBuffers(false);
}

void map::ChunkRenderer::render(const engine::ScenePtr scene) {
	worldRenderer->getShader()->setChunkPos(chunkPos);
	drawTriangles();
}

