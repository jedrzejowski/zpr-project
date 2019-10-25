#include "renderer.h"
#include "chunk.h"
#include "chunkRenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"

map::Renderer::Renderer(const engine::Scene *scene,
						const game::Player *player,
						const map::WorldMap *worldMap) :
		Object() {
	this->scene = scene;
	this->player = player;
	this->worldMap = worldMap;

	shader = new engine::Shader("shader/game.vert", "shader/game.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = engine::Resources::get().getTexture("texture.png");


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

void map::Renderer::render(engine::Scene *scene) {

	shader->bind();
	blockTexture->use();

//	glEnable(GL_CULL_FACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	shader->setMat4("projection", glm::perspective(glm::radians(45.0f),
												   (float) this->scene->getWindow()->getSceneWidth() /
												   (float) this->scene->getWindow()->getSceneHeight(),
												   0.1f, 100.0f));

	auto camera = player->getCamera();
	shader->setMat4("camera", camera.getMatrix());
	shader->setVec3("cameraPos", camera.position);

	for (auto *chunkRenderer : chunkRenderers)
		chunkRenderer->render(scene);

	shader->unbind();
}

engine::Shader *map::Renderer::getShader() const {
	return shader;
}
