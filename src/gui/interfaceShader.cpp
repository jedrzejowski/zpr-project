//
// Created by adam on 06.11.2019.
//

#include "interfaceShader.h"

gui::InterfaceShader::InterfaceShader() {
	shader = new engine::ShaderProgram("shader/interface.vert", "shader/interface.frag");
	guiTexture = engine::Resources::get().getTexture("texture/gui.png");
	fontTexture = engine::Resources::get().getTexture("texture/font.png");

	shader->bind();
	shader->setUniformNameToId("guiTexture", 0);
	shader->setUniformNameToId("fontTexture", 1);
	shader->unbind();
}

void gui::InterfaceShader::bind() {
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->bind();

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	guiTexture->use(0);
	fontTexture->use(1);
}

void gui::InterfaceShader::unbind() {
	glDisable(GL_BLEND);
	shader->unbind();
}

void gui::InterfaceShader::setModel(const glm::mat4 &model) {
	shader->setMat4("model", model);
}


