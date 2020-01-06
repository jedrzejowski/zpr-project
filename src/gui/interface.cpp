//
// Created by adam on 25.10.2019.
//

#include "interface.h"

gui::Interface::Interface() : Abs3DObj() {

	inputInterface = std::make_shared<engine::InputInterface>();

	// Przeliczenie względnej pozycji myszki na dziedzinę interfejsu
	inputInterface->getMouse()->onMove([&](const glm::vec2 &delta) {
		auto mousePosition = inputInterface->getMouse()->getCurrentPosition();

		auto sceneWPtr = inputInterface->getScene();
		if (sceneWPtr.expired()) return;
		auto scenePtr = sceneWPtr.lock();
		auto winWPtr = scenePtr->getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();

		mousePosition.x -= float(winPtr->getWinWidth()) / 2 + 0.5;
		mousePosition.y -= float(winPtr->getWinHeight()) / 2 + 0.5;
		auto size = std::min(winPtr->getWinWidth(), winPtr->getWinHeight());
		mousePosition.x /= size;
		mousePosition.y /= size;
		mousePosition.x += 0.5;
		mousePosition.y += 0.5;
		mousePosition /= getScaleSize();

		mouseScaledPosition = mousePosition;
	});
}


void gui::Interface::render(const engine::ScenePtr& scene) {
	auto windowWPtr = scene->getWindow();

	if (windowWPtr.expired()) {
		logger.err("gui::Interface::render(): rendering with expired Window object");
		return;
	}

	auto window = windowWPtr.lock();

	window->setViewPort(engine::ViewPort::Square);

	interfaceShader.bind();
	interfaceShader.setModel(getModel());

	drawTriangles();

	interfaceShader.unbind();
}

engine::InputInterfacePtr gui::Interface::getInputInterface() {
	return inputInterface;
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
