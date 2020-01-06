#include "worldRenderer.h"

#include <utility>
#include "chunk.h"
#include "chunkRenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"
#include "src/game/selectedBlock.h"
#include "worldShader.h"

map::WorldRenderer::WorldRenderer(const map::WorldPtr &worldMap) :
		worldMap(worldMap) {
	logger.constructor(this);

	shader = std::make_shared<map::WorldShader>();
	blockTexture = engine::Resources::get().getTexture("texture/block.png");
}

map::WorldRendererPtr map::WorldRenderer::create(const map::WorldPtr &worldMap) {
	struct trick : WorldRenderer {
		trick(const map::WorldPtr &worldMap) : WorldRenderer(worldMap) {}
	};

	map::WorldRendererPtr self = std::make_shared<trick>(worldMap);

	self->initEvents();

	return self;
}


void map::WorldRenderer::initEvents() {
	auto tt = this->shared_from_this();

	worldMap->onChunkInserted(this->shared_from_this(), [&](const map::ChunkPtr& chunk) {

		auto self = this->shared_from_this();
		auto cr = ChunkRenderer::create(self, chunk);
		chunkRenderers[chunk->getPosition()] = cr;
	});

	worldMap->onChunkEjected(this->shared_from_this(), [&](const map::ChunkPtr &chunk) {
		chunkRenderers.erase(chunk->getPosition());
	});
}


map::WorldRenderer::~WorldRenderer() {
	logger.destructor(this);
}

void map::WorldRenderer::render(const engine::Camera &camera,
								const engine::ScenePtr& scene) {
	auto window = scene->getWindow().lock();
	window->setViewPort(engine::ViewPort::OneTwoOne);

	glClear(GL_DEPTH_BUFFER_BIT);

	shader->bind();
	blockTexture->use();

//	glEnable(GL_CULL_FACE); // tak aby tyły nie były renderowane

	shader->setProjection(glm::perspective(glm::radians(45.0f),
										   (float) window->getWinWidth() /
										   (float) window->getWinHeight(),
										   0.1f, 100.0f));

	shader->setCamera(camera);

	for (const auto &it : chunkRenderers)
		it.second->render(scene);

	shader->unbind();
}

map::WorldShaderPtr map::WorldRenderer::getShader() const {
	return shader;
}
