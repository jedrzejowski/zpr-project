/**
 * @file WorldRenderer.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldRenderer.h"

#include <utility>
#include "Chunk.h"
#include "ChunkRenderer.h"
#include "src/game/Player.h"
#include "src/engine/Engine.h"
#include "WorldShader.h"

map::WorldRenderer::WorldRenderer(const map::WorldPtr& worldMap) :
		world_map_ptr(worldMap) {
	logger(1).constructor(this);

	shader = std::make_shared<map::WorldShader>();
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

	world_map_ptr->onChunkInserted(this->shared_from_this(), [&](const map::ChunkPtr& chunk) {

		auto self = this->shared_from_this();
		auto cr = ChunkRenderer::create(self, chunk);
		chunk_renderers[chunk->getPosition()] = cr;
	});

	world_map_ptr->onChunkEjected(this->shared_from_this(), [&](const map::ChunkPtr &chunk) {
		chunk_renderers.erase(chunk->getPosition());
	});
}


map::WorldRenderer::~WorldRenderer() {
	logger(1).destructor(this);
}

void map::WorldRenderer::render(const engine::Camera &camera,
								const engine::ScenePtr& scene) {
	auto window = scene->getWindow().lock();
	window->setViewPort(engine::ViewPort::OneTwoOne);

	glClear(GL_DEPTH_BUFFER_BIT);

	shader->bind();

//	glEnable(GL_CULL_FACE); // tak aby tyły nie były renderowane

	shader->setProjection(glm::perspective(glm::radians(45.0f),
										   (float) window->getWinWidth() /
										   (float) window->getWinHeight(),
										   0.1f, 100.0f));

	shader->setCamera(camera);

	for (const auto &it : chunk_renderers)
		it.second->render(scene);

	shader->unbind();
}

map::WorldShaderPtr map::WorldRenderer::getShader() const {
	return shader;
}
