//
// Created by adam on 06.11.2019.
//

#include "interfaceShader.h"

gui::InterfaceShader::InterfaceShader() {
	shader = new engine::ShaderProgram("shader/interface.vert", "shader/interface.frag");
	guiTexture = engine::Resources::get().getTexture("texture/gui.png");
	fontTexture = engine::Resources::get().getTexture("texture/font.png");
}

void gui::InterfaceShader::bind() {
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->bind();
}

void gui::InterfaceShader::unbind() {
	shader->unbind();
}


