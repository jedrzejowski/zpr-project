#include "worldRenderer.h"
#include "chunk.h"
#include "chunkRenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"

map::WorldRenderer::WorldRenderer(const map::WorldPtr &worldMap) :
		worldMap(worldMap) {

	shader = new engine::ShaderProgram("shader/game.vert", "shader/game.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = engine::Resources::get().getTexture("texture/block.png");

	worldMap->onChunkInserted([&](map::ChunkPtr chunk) {

		auto cr = std::make_shared<ChunkRenderer>(this, chunk);
		chunkRenderers.push_back(cr);
	});
}

map::WorldRenderer::~WorldRenderer() {
}

void map::WorldRenderer::render(const engine::Camera &camera,
								const engine::Scene *scene) {
	auto window = scene->getWindow();
	window->setViewPort(engine::ViewPort::OneTwoOne);

	glClear(GL_DEPTH_BUFFER_BIT);

	shader->bind();
	blockTexture->use();

//	glEnable(GL_CULL_FACE);

	shader->setMat4("projection",
					glm::perspective(glm::radians(45.0f),
									 (float) scene->getWindow()->getWinWidth() /
									 (float) scene->getWindow()->getWinHeight(),
									 0.1f, 100.0f));

	shader->setMat4("camera", camera.getMatrix());
	shader->setVec3("cameraPos", camera.position);

	for (auto &chunkRenderer : chunkRenderers)
		chunkRenderer->render(scene);

	shader->unbind();
}

engine::ShaderProgram *map::WorldRenderer::getShader() const {
	return shader;
}

void map::WorldRenderer::syncWithWorld() {
}

void map::WorldRenderer::injectChunkRenderer(map::ChunkRendererPtr &chunkRenderer) {
}

void map::WorldRenderer::ejectChunkRenderer(map::ChunkRendererPtr &chunkRenderer) {
}

