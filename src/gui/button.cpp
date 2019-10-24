//
// Created by adam on 24.10.2019.
//

#include "button.h"

gui::Button::Button() {

	texture = engine::Resources::get().getTexture("texture/gui-buttons.png");

	vertices.emplace_back(0.f, 0.f, 0.f, engine::TexCoord(0.f, 0.f));
	vertices.emplace_back(1.f, 0.f, 0.f, engine::TexCoord(2.f, 0.f));
	vertices.emplace_back(1.f, 1.f, 0.f, engine::TexCoord(2.f, 2.f));
	vertices.emplace_back(0.f, 1.f, 0.f, engine::TexCoord(0.f, 2.f));
	indices.emplace_back(0, 1, 2);
	indices.emplace_back(2, 3, 0);
	insertObjToBuffers();
}

void gui::Button::render(engine::Scene *scene) {
	texture->use();
	draw();
}
