/**
 * @file InterfaceShader.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "InterfaceShader.h"

gui::InterfaceShader::InterfaceShader() : Shader("shader/interface.vert", "shader/interface.frag") {
	static auto &resources = engine::Resources::get();
	gui_texture = resources.getTexture("texture/gui.png");
	font_texture = resources.getTexture("texture/font.png");
	block_texture = resources.getTexture("texture/block.png");

	program.bind();
	program.setUniformNameToId("block_texture", global::TextureBlocksNo);
	program.setUniformNameToId("gui_texture", global::TextureGuiNo);
	program.setUniformNameToId("font_texture", global::TextureFontNo);
	program.unbind();
}

void gui::InterfaceShader::bind() {
	glClear(GL_DEPTH_BUFFER_BIT);
	program.bind();

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	block_texture->use(global::TextureBlocksNo);
	gui_texture->use(global::TextureGuiNo);
	font_texture->use(global::TextureFontNo);
}

void gui::InterfaceShader::unbind() {
	glDisable(GL_BLEND);
	program.unbind();
}

void gui::InterfaceShader::setModel(const glm::mat4 &model) {
	program.setMat4("model", model);
}


