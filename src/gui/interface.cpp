//
// Created by adam on 25.10.2019.
//

#include "interface.h"
#include "guiObj.h"

gui::Interface::Interface(engine::Scene *parent) :
		Object(parent) {

	shader = new engine::Shader("shader/interface.vert", "shader/interface.frag");
	texture = engine::Resources::get().getTexture("texture/interface.png");
}

void gui::Interface::addObject(glm::vec3 position, gui::GuiObject *object) {

	objects.push_back(new InterfaceItem{
			position,
			object
	});

	needBufferRefresh = true;
}

void gui::Interface::removeObject(gui::GuiObject *object) {
	for (const auto iter : objects) {
		if (iter->object == object) {
			objects.remove(iter);
			return;
		}
	}

	needBufferRefresh = true;
}

void gui::Interface::render(engine::Scene *scene) {
	shader->bind();
	texture->use();

	if (needBufferRefresh)
		refreshBuffers();

	draw();

	shader->unbind();
}

void gui::Interface::refreshBuffers() {

	vertices.clear();
	indices.clear();

	for (auto iter : objects) {
		iter->object->insertToBuffers(vertices, indices);
	}

	insertObjToBuffers();

	needBufferRefresh = false;
}
