#include "renderer.h"
#include "chunk.h"
#include "chunkRenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"

map::Renderer::Renderer(const map::WorldMap *worldMap) :
		Object() {
	this->worldMap = worldMap;

	shader = new engine::Shader("shader/game.vert", "shader/game.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = engine::Resources::get().getTexture("texture/block.png");


	worldMap->loadChunk(coord2D(0, 0));
	worldMap->loadChunk(coord2D(1, 0));
	worldMap->loadChunk(coord2D(1, 1));
	worldMap->loadChunk(coord2D(0, 1));
	chunkRenderers.push_back(new map::ChunkRenderer(this, worldMap->getChunk(coord2D(0, 0))));
	chunkRenderers.push_back(new map::ChunkRenderer(this, worldMap->getChunk(coord2D(1, 0))));
	chunkRenderers.push_back(new map::ChunkRenderer(this, worldMap->getChunk(coord2D(1, 1))));
	chunkRenderers.push_back(new map::ChunkRenderer(this, worldMap->getChunk(coord2D(0, 1))));
}

map::Renderer::~Renderer() {
}

void map::Renderer::render(const engine::Camera &camera,
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

	for (auto *chunkRenderer : chunkRenderers)
		chunkRenderer->render(scene);

	shader->unbind();
}

engine::Shader *map::Renderer::getShader() const {
	return shader;
}
