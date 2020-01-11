/**
 * @file Interface.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Interface.h"

gui::Interface::Interface() : Abs3DObj() {

	input_interface_ptr = std::make_shared<engine::InputInterface>();

	// Przeliczenie względnej pozycji myszki na dziedzinę interfejsu
	input_interface_ptr->getMouse()->onMove([&](const glm::vec2 &delta) {
		auto mousePosition = input_interface_ptr->getMouse()->getCurrentPosition();

		auto sceneWPtr = input_interface_ptr->getScene();
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

		mouse_scaled_position = mousePosition;
	});
}


void gui::Interface::render(const engine::ScenePtr& scene) {
	auto windowWPtr = scene->getWindow();

	if (windowWPtr.expired()) {
		logger(1).err("gui::Interface::render(): rendering with expired Window object");
		return;
	}

	auto window = windowWPtr.lock();

	window->setViewPort(engine::ViewPort::Square);

	interface_shader.bind();
	interface_shader.setModel(getModel());

	drawTriangles();

	interface_shader.unbind();
}

engine::InputInterfacePtr gui::Interface::getInputInterface() {
	return input_interface_ptr;
}

const glm::vec2 &gui::Interface::getScaleSize() const {
	return scale_size;
}

void gui::Interface::setScaleSize(const glm::vec2 &scaleSize) {
	Interface::scale_size = scaleSize;
}

glm::mat4 gui::Interface::getModel() {
	auto topLeft = glm::mat4(1);

	// odbicie lustrazne względem osi Y
	topLeft[1][1] = -1.f;
	// przeniesienie do górnego lewego obszaru
	topLeft = glm::translate(topLeft, glm::vec3(-1, -1, 0));
	topLeft = glm::scale(topLeft, glm::vec3(2));
	topLeft = glm::scale(topLeft, glm::vec3(1 / scale_size.x, 1 / scale_size.y, 1));

	return topLeft;
}

glm::vec2 gui::Interface::getMouseScaledPosition() {
	return mouse_scaled_position;
}
