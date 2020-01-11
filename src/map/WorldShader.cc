/**
 * @file WorldShader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldShader.h"

map::WorldShader::WorldShader() : Shader("shader/game.vert", "shader/game.frag") {

	block_texture = engine::Resources::get().getTexture("texture/block.png");
	program.setInt("material.diffuse", 0);
}

void map::WorldShader::setCamera(const engine::Camera &camera) {
	program.setMat4("camera", camera.getMatrix());
	program.setVec3("cameraPos", camera.position);
}

void map::WorldShader::setProjection(const glm::mat4 &mat) {
	program.setMat4("projection", mat);
}

void map::WorldShader::setChunkPos(const glm::mat4 &mat) {
	program.setMat4("chunk_position", mat);
}

void map::WorldShader::bind() {
	block_texture->use();
	Shader::bind();
}

