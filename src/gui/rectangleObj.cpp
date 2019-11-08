#include "rectangleObj.h"
#include "interface.h"

gui::RectangleObj::RectangleObj(Interface *interface) :
		GuiObject(interface) {


	interface->getInputInterface()->getMouse()->onMove(this, [this](const glm::vec2 &delta) {

		auto mousePosition = this->getInterface()->getMouseScaledPosition();
//		mousePosition = this->getModel() * glm::vec4(mousePosition, 0, 1);
		bool isCollision = isCollisionWithMouse(mousePosition);

		if (isCollision) {
			if (!isMouseIn)
				onEnter();
			onHover();
		} else {
			if (isMouseIn)
				onLeave();
		}

		isMouseIn = isCollision;
	});

	interface->getInputInterface()->getMouse()->Left.onPressed(this, [&] {
		if (isMouseIn) onPressed();
	});

	interface->getInputInterface()->getMouse()->Left.onReleased(this, [&] {
		if (isMouseIn) onReleased();
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

const glm::vec2 &gui::RectangleObj::getTextureStart() const {
	return textureStart;
}

void gui::RectangleObj::setTextureStart(const glm::vec2 &textureStart) {
	RectangleObj::textureStart = textureStart;

	setNeedRefreshBuffers(true);
}

const glm::vec2 &gui::RectangleObj::getTextureEnd() const {
	return textureEnd;
}

void gui::RectangleObj::setTextureEnd(const glm::vec2 &textureEnd) {
	RectangleObj::textureEnd = textureEnd;

	setNeedRefreshBuffers(true);
}

void gui::RectangleObj::setTexture(const glm::vec2 &textureStart, const glm::vec2 &textureEnd) {
	setTextureStart(textureStart);
	setTextureEnd(textureEnd);
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

	verticesBuf.clear();
	verticesBuf.emplace_back(point_xy, engine::TexCoord(textureStart.x, textureStart.y));
	verticesBuf.emplace_back(point_Xy, engine::TexCoord(textureEnd.x, textureStart.y));
	verticesBuf.emplace_back(point_XY, engine::TexCoord(textureEnd.x, textureEnd.y));
	verticesBuf.emplace_back(point_xY, engine::TexCoord(textureStart.x, textureEnd.y));

	indicesBuf.clear();
	indicesBuf.emplace_back(0, 1, 2);
	indicesBuf.emplace_back(2, 3, 0);
}

