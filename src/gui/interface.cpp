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

	setNeedRefreshBuffers(true);
}

void gui::Interface::removeObject(gui::GuiObject *object) {
	for (const auto iter : objects) {
		if (iter->object == object) {
			objects.remove(iter);
			return;
		}
	}

	setNeedRefreshBuffers(true);
}

void gui::Interface::render(const engine::Scene *scene) {

	shader->bind();
	texture->use();

	auto window = scene->getWindow();
	if (window != nullptr) {
		auto topLeft = glm::mat4(1);
		// odbicie lustrazne względem osi Y
		topLeft[1][1] = -1.f;
		// przeniesienie do górnego lewego obszaru
		topLeft = glm::translate(topLeft, glm::vec3(-1, -1, 0));
		shader->setMat4("topLeft", topLeft);
	}

	draw();

	shader->unbind();
}

void gui::Interface::updateBuffers() {

	vertices.clear();
	indices.clear();

	for (auto iter : objects) {
		iter->object->insertToBuffers(vertices, indices);
	}
}
