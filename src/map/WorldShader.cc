/**
 * @file WorldShader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldShader.h"
#include "src/lib/AppSettings.h"

map::WorldShader::WorldShader() : Shader("shader/game.vert", "shader/game.frag") {
	static auto &resources = engine::Resources::get();
	block_texture = resources.getTexture("texture/block.png");
	program.setInt("material.diffuse", 0);
}

void map::WorldShader::setCamera(const engine::Camera &camera) {
	program.setMat4("camera", camera.getMatrix());
	program.setVec3("cameraPos", camera.position);
}

void map::WorldShader::setProjection(const glm::mat4 &mat) {
	program.setMat4("projection", mat);
}

void map::WorldShader::updateProjection(const engine::WindowPtr &window_ptr) {

	static auto &app_settings = AppSettings::get();

	setProjection(
			glm::perspective(
					glm::radians(app_settings.playerCameraAngle.get()),
					(float) window_ptr->getWinWidth() / (float) window_ptr->getWinHeight(),
					0.1f, 100.0f
			)
	);
}

void map::WorldShader::setChunkPos(const glm::mat4 &mat) {
	program.setMat4("chunk_position", mat);
}

void map::WorldShader::bind() {
	block_texture->use();
	Shader::bind();
}