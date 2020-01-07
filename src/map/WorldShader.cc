//
// Created by adam on 05.01.2020.
//

#include "WorldShader.h"

map::WorldShader::WorldShader() : Shader("shader/game.vert", "shader/game.frag") {

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
	program.setMat4("chunkPos", mat);
}

