#include "ChunkRenderer.h"
#include "WorldRenderer.h"
#include "Chunk.h"
#include "WorldShader.h"

map::ChunkRenderer::ChunkRenderer(map::WorldRendererPtr &renderer, const map::ChunkPtr &chunkPtr) :
		Abs3DObj(),
		worldRenderer(renderer),
		chunk(chunkPtr) {
	logger.constructor(this);
}

map::ChunkRendererPtr map::ChunkRenderer::create(map::WorldRendererPtr &renderer, const map::ChunkPtr &chunkPtr) {
	struct Self : ChunkRenderer {
		Self(map::WorldRendererPtr &renderer, const map::ChunkPtr &chunkPtr) : ChunkRenderer(renderer, chunkPtr) {}
	};

	auto self = std::make_shared<Self>(renderer, chunkPtr);

	self->initEvents();

	return self;
}

void map::ChunkRenderer::initEvents() {
	chunk->onBlockChange([&](const Coord3D &pos) {
		setNeedRefreshBuffers(true);
	});
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

	verticesBuf.clear();
	indicesBuf.clear();

	for (const auto &iter : chunk->getAllBlocks()) {
		if (iter.second == nullptr) continue;
		iter.second->insertToBuffers(verticesBuf, indicesBuf);
	}

	setNeedRefreshBuffers(false);
}

void map::ChunkRenderer::render(const engine::ScenePtr& scene) {
	worldRenderer.lock()->getShader()->setChunkPos(chunkPos);
	drawTriangles();
}
