#include "renderer.h"
#include "chunk.h"
#include "chunkrenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"

map::Renderer::Renderer(const engine::Scene *scene,
						const game::Player *player,
						const map::WorldMap *worldMap) :
		Object() {
	this->scene = scene;
	this->player = player;
	this->worldMap = worldMap;

	shader = new engine::Shader("shader/basic.vert", "shader/basic.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = engine::Resources::get().getTexture("texture.png");

	for (auto chunk : worldMap->getVisibleChunk()) {
		chunkRenderers.push_back(new map::ChunkRenderer(chunk));
	}
}

map::Renderer::~Renderer() {
}

void map::Renderer::render(engine::Scene *scene) {

	shader->use();
	blockTexture->use();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	shader->setMat4("projection", glm::perspective(glm::radians(45.0f),
												   (float) this->scene->getWindow()->getWidth() /
												   (float) this->scene->getWindow()->getHeight(),
												   0.1f, 100.0f));

	auto &camera = player->getCamera();
	shader->setMat4("camera", camera.getMatrix());
	shader->setVec3("cameraPos", camera.position);


	shader->setMat4("model", glm::mat4(1.0f));

	for (auto *chunkRenderer : chunkRenderers)
		chunkRenderer->render(scene);
}
