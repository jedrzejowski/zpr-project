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

map::WorldRenderer::WorldRenderer(const map::WorldPtr &worldMap) :
		world_map_ptr(worldMap) {
	logger(4).constructor(this);

	shader = std::make_shared<map::WorldShader>();
}

map::WorldRendererPtr map::WorldRenderer::create(const map::WorldPtr &worldMap) {
	struct Self : WorldRenderer {
		Self(const map::WorldPtr &worldMap) : WorldRenderer(worldMap) {}
	};

	map::WorldRendererPtr self = std::make_shared<Self>(worldMap);
	self->constructorWorldRenderer();
	return self;
}


void map::WorldRenderer::constructorWorldRenderer() {
	auto self = this->shared_from_this();

	world_map_ptr->onChunkInserted(self, [&](const map::ChunkPtr &chunk) {
		auto self = this->shared_from_this();
		auto cr = ChunkRenderer::create(self, chunk);
		chunk_renderers[chunk->getPosition()] = cr;
	});

	world_map_ptr->onChunkEjected(self, [&](const map::ChunkPtr &chunk) {
		chunk_renderers.erase(chunk->getPosition());
	});
}


map::WorldRenderer::~WorldRenderer() {
	logger(4).destructor(this);
}

void map::WorldRenderer::render(const engine::Camera &camera,
								const engine::ScenePtr &scene) {
	auto window_ptr = scene->getWindow().lock();
	window_ptr->setViewPort(engine::ViewPort::OneTwoOne);

	glClear(GL_DEPTH_BUFFER_BIT);

	shader->bind();

//	glEnable(GL_CULL_FACE); // tak aby tyły nie były renderowane

	shader->updateProjection(window_ptr);
	shader->setCamera(camera);

	// tu przedało by się sprawdzać czy dany chunk powinien być renderowany
	for (const auto &it : chunk_renderers)
		it.second->render(scene);

	shader->unbind();
}

map::WorldShaderPtr map::WorldRenderer::getShader() const {
	return shader;
}
map::ChunkRendererWPtr map::WorldRenderer::getChunkRenderer(const Coord2D &position) {
	if (chunk_renderers.count(position) == 1) {
		return chunk_renderers[position];
	} else return map::ChunkRendererWPtr();
}
