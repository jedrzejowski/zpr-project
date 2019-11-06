//
// Created by adam on 25.10.2019.
//

#include "interface.h"

gui::Interface::Interface(engine::Scene *parent) :
		Object(parent),
		scene(parent) {
	inputInterface = new engine::InputInterface(this);

	// Przeliczenie względnej pozycji myszki na dziedzinę interfejsu
	inputInterface->getMouse()->onMove([&](const glm::vec2 &delta) {
		auto mousePosition = inputInterface->getMouse()->getCurrentPosition();

		auto scene = inputInterface->getScene();
		if (scene == nullptr) return;
		auto win = scene->getWindow();
		if (win == nullptr) return;

		mousePosition.x -= float(win->getWinWidth()) / 2 + 0.5;
		mousePosition.y -= float(win->getWinHeight()) / 2 + 0.5;
		auto size = std::min(win->getWinWidth(), win->getWinHeight());
		mousePosition.x /= size;
		mousePosition.y /= size;
		mousePosition.x += 0.5;
		mousePosition.y += 0.5;
		mousePosition /= getScaleSize();

		mouseScaledPosition = mousePosition;
	});
}


void gui::Interface::render(const engine::Scene *scene) {
	auto window = scene->getWindow();
	auto size = std::min(window->getWinWidth(), window->getWinHeight());
	window->setViewPort(engine::ViewPort::Square);

	interfaceShader.bind();
	interfaceShader.setModel(getModel());

	draw();

	interfaceShader.unbind();
}

engine::InputInterface *gui::Interface::getInputInterface() const {
	return inputInterface;
}

engine::Scene *gui::Interface::getScene() const {
	return scene;
}

const glm::vec2 &gui::Interface::getScaleSize() const {
	return scaleSize;
}

void gui::Interface::setScaleSize(const glm::vec2 &scaleSize) {
	Interface::scaleSize = scaleSize;
}

glm::mat4 gui::Interface::getModel() {
	auto topLeft = glm::mat4(1);

	// odbicie lustrazne względem osi Y
	topLeft[1][1] = -1.f;
	// przeniesienie do górnego lewego obszaru
	topLeft = glm::translate(topLeft, glm::vec3(-1, -1, 0));
	topLeft = glm::scale(topLeft, glm::vec3(2));
	topLeft = glm::scale(topLeft, glm::vec3(1 / scaleSize.x, 1 / scaleSize.y, 1));

	return topLeft;
}

glm::vec2 gui::Interface::getMouseScaledPosition() {
	return mouseScaledPosition;
}
