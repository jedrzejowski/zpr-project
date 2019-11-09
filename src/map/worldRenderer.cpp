#include "worldRenderer.h"
#include "chunk.h"
#include "chunkRenderer.h"
#include "src/game/player.h"
#include "src/engine/Engine.h"

map::WorldRenderer::WorldRenderer(const map::World *worldMap) :
		worldMap(worldMap),
		Object() {

	shader = new engine::ShaderProgram("shader/game.vert", "shader/game.frag");
	shader->setInt("material.diffuse", 0);
	blockTexture = engine::Resources::get().getTexture("texture/block.png");
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

	for (auto *chunkRenderer : chunkRenderers)
		chunkRenderer->render(scene);

	shader->unbind();
}

engine::ShaderProgram *map::WorldRenderer::getShader() const {
	return shader;
}
