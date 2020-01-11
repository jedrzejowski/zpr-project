/**
 * @file RectangleObj.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "RectangleObj.h"
#include "Interface.h"

gui::RectangleObj::RectangleObj(InterfacePtr interface) : GuiObject(interface) {
}

void gui::RectangleObj::initInputInterface() {

	auto ii = getInterface()->getInputInterface();
	auto self = this->shared_from_this();

	ii->getMouse()->onMove(self, [this](const glm::vec2 &delta) {

		auto mousePosition = this->getInterface()->getMouseScaledPosition();
//		mousePosition = this->getModel() * glm::vec4(mousePosition, 0, 1);
		bool isCollision = isCollisionWithMouse(mousePosition);

		if (isCollision) {
			if (!is_mouse_in)
				onEnter();
			onHover();
		} else {
			if (is_mouse_in)
				onLeave();
		}

		is_mouse_in = isCollision;
	});

	ii->getMouse()->Left.onPressed(self, [&] {
		if (is_mouse_in) onPressed();
	});

	ii->getMouse()->Left.onReleased(self, [&] {
		if (is_mouse_in) onReleased();
	});
}

bool gui::RectangleObj::isCollisionWithMouse(const glm::vec2 &mousePosition) {
	return point_xy.x < mousePosition.x && mousePosition.x < point_XY.x &&
		   point_xy.y < mousePosition.y && mousePosition.y < point_XY.y;
}

const glm::vec2 &gui::RectangleObj::getPosition() const {
	return position;
}

void gui::RectangleObj::setPosition(const glm::vec2 &position) {
	RectangleObj::position = position;
	refreshModel();
}

const glm::vec2 &gui::RectangleObj::getSize() const {
	return size;
}

void gui::RectangleObj::setSize(const glm::vec2 &size) {
	RectangleObj::size = size;
	refreshModel();
}


void gui::RectangleObj::refreshModel() {
	auto recModel = glm::mat4(1);
	recModel = glm::translate(recModel, glm::vec3(position, 0));
	recModel = glm::scale(recModel, glm::vec3(size, 1));
	setModel(recModel);
}


void gui::RectangleObj::updateBuffers() {

	auto baseSize = getBaseSize();

	point_xy = getModel() * glm::vec4(0, 0, 0, 1);
	point_Xy = getModel() * glm::vec4(baseSize.x, 0, 0, 1);
	point_XY = getModel() * glm::vec4(baseSize.x, baseSize.y, 0, 1);
	point_xY = getModel() * glm::vec4(0, baseSize.y, 0, 1);

	vertices_buffer.clear();
	vertices_buffer.emplace_back(point_xy, texture_reference.getTexCoord_xy());
	vertices_buffer.emplace_back(point_Xy, texture_reference.getTexCoord_Xy());
	vertices_buffer.emplace_back(point_XY, texture_reference.getTexCoord_XY());
	vertices_buffer.emplace_back(point_xY, texture_reference.getTexCoord_xY());

	indices_buffer.clear();
	indices_buffer.emplace_back(0, 1, 2);
	indices_buffer.emplace_back(2, 3, 0);
}

const engine::SquareTextureReference &gui::RectangleObj::getTextureReference() const {
	return texture_reference;
}

void gui::RectangleObj::setTextureReference(const engine::SquareTextureReference &textureReference) {
	RectangleObj::texture_reference = textureReference;
	setNeedRefreshBuffers(true);
}

