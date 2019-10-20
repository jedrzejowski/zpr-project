#include "renderer.h"
#include "chunk.h"
#include "chunkrenderer.h"

map::Renderer::Renderer(map::WorldMap *worldMap) {
	this->worldMap = worldMap;

	shader = new gengine::Shader("shader/basic.vert", "shader/basic.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = gengine::Resources::get().getTexture("texture.png");

	for(auto chunk : worldMap->getVisibleChunk()){
		chunkRenderers.push_back(new map::ChunkRenderer(chunk));
	}

}

map::Renderer::~Renderer() {
}

void map::Renderer::render() {

	shader->use();

	gengine::Camera camera{};
	camera.position = glm::vec3(-4.0f);
	camera.front = glm::vec3(4.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	light = new gengine::Light();
	light->position = glm::vec3(5.0f, 4.0f, -3.0f);
	light->ambient = glm::vec3(0.2f);
	light->diffuse = glm::vec3(0.5f);
	light->specular = glm::vec3(1.0f);

	shader->setMat4("projection", glm::perspective(glm::radians(45.0f), (float) 100 / (float) 100, 0.1f, 100.0f));
	shader->setMat4("camera", camera.getMatrix());
	shader->setVec3("cameraPos", camera.position);

	shader->setLight("light", *light);
	shader->setMat4("model", glm::mat4(1.0f));

	shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	shader->setFloat("material.shininess", 64.0f);


	for (auto *chunkRenderer : chunkRenderers) {
		chunkRenderer->render();
	}
}

map::WorldMap *map::Renderer::getWorldMap() const {
	return worldMap;
}
