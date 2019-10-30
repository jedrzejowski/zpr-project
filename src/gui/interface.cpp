//
// Created by adam on 25.10.2019.
//

#include "interface.h"
#include "guiObj.h"

gui::Interface::Interface(engine::Scene *parent) :
		Object(parent),
		scene(parent) {
	inputInterface = new engine::InputInterface(this);
	shader = new engine::Shader("shader/interface.vert", "shader/interface.frag");
	texture = engine::Resources::get().getTexture("texture/gui.png");


	inputInterface->onAttached([&] {
		updateMouseState(true);
	});

	inputInterface->getMouse()->onMove([&](const glm::vec2 &delta) {
		updateMouseState();
	});

	inputInterface->getMouse()->Left.onPressed([&] {
		updateMouseState();
	});
}


void gui::Interface::addObject(glm::vec2 position, glm::vec2 size, gui::GuiObject *object) {
	auto model = glm::mat4(1);
	model = glm::scale(model, glm::vec3(size, 1.f));
	model = glm::translate(model, glm::vec3(position, 0.f));
	addObject(model, object);
}


void gui::Interface::addObject(glm::mat4 model, gui::GuiObject *object) {

	objects.push_back(new InterfaceItem{
			model,
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
	auto window = scene->getWindow();
	auto size = std::min(window->getWinWidth(), window->getWinHeight());

	window->setViewPort(engine::ViewPort::Square);
	glClear(GL_DEPTH_BUFFER_BIT);

	shader->bind();
	texture->use();

	{
		auto topLeft = glm::mat4(1);
		// odbicie lustrazne względem osi Y
		topLeft[1][1] = -1.f;
		// przeniesienie do górnego lewego obszaru
		topLeft = glm::translate(topLeft, glm::vec3(-1, -1, 0));
		topLeft = glm::scale(topLeft, glm::vec3(2));
		shader->setMat4("topLeft", topLeft);
	}

	draw();

	shader->unbind();
}

void gui::Interface::updateBuffers() {

	vertices.clear();
	indices.clear();

	for (auto iter : objects) {
		iter->object->setModel(iter->model);
		iter->object->insertToBuffers(vertices, indices);
	}
}

engine::InputInterface *gui::Interface::getInputInterface() const {
	return inputInterface;
}

engine::Scene *gui::Interface::getScene() const {
	return scene;
}


void gui::Interface::updateMouseState(bool initial) {
	auto mouse = getInputInterface()->getMouse();

	for (auto iter : objects) {
		if (initial) {
			iter->wasIn = false;
		}

		if (iter->object->isCollisionWithMouse(mouse)) {
			if (iter->wasIn) {


			} else {
				iter->object->onHover();
				iter->wasIn = true;
			}
		} else {
			if (iter->wasIn) {
				iter->object->onLeave();
				iter->wasIn = false;
			}
		}
	}
}
