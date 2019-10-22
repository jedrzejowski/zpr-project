#include "renderer.h"
#include "chunk.h"
#include "chunkrenderer.h"

map::Renderer::Renderer(map::WorldMap *worldMap) : Object() {
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

	engine::Camera camera{};
	camera.position = glm::vec3(-4.0f);
	camera.front = glm::vec3(4.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);


	shader->setMat4("projection", glm::perspective(glm::radians(45.0f), (float) 100 / (float) 100, 0.1f, 100.0f));
	shader->setMat4("camera", camera.getMatrix());
	shader->setVec3("cameraPos", camera.position);

	shader->setMat4("model", glm::mat4(1.0f));


	for (auto *chunkRenderer : chunkRenderers) {
		chunkRenderer->render(scene);
	}
}

map::WorldMap *map::Renderer::getWorldMap() const {
	return worldMap;
}
