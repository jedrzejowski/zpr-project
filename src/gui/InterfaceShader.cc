/**
 * @file InterfaceShader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InterfaceShader.h"

gui::InterfaceShader::InterfaceShader() : Shader("shader/interface.vert", "shader/interface.frag") {
	guiTexture = engine::Resources::get().getTexture("texture/gui.png");
	fontTexture = engine::Resources::get().getTexture("texture/font.png");
	blockTexture = engine::Resources::get().getTexture("texture/block.png");

	program.bind();
	program.setUniformNameToId("blockTexture", global::TextureBlocksNo);
	program.setUniformNameToId("guiTexture", global::TextureGuiNo);
	program.setUniformNameToId("fontTexture", global::TextureFontNo);
	program.unbind();
}

void gui::InterfaceShader::bind() {
	glClear(GL_DEPTH_BUFFER_BIT);
	program.bind();

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	blockTexture->use(global::TextureBlocksNo);
	guiTexture->use(global::TextureGuiNo);
	fontTexture->use(global::TextureFontNo);
}

void gui::InterfaceShader::unbind() {
	glDisable(GL_BLEND);
	program.unbind();
}

void gui::InterfaceShader::setModel(const glm::mat4 &model) {
	program.setMat4("model", model);
}


