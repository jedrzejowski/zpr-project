#include "RectangleObj.h"
#include "Interface.h"

gui::RectangleObj::RectangleObj(InterfacePtr interface) :
		GuiObject(interface) {
}

void gui::RectangleObj::initInputInterface() {

	auto ii = getInterface()->getInputInterface();
	auto self = this->shared_from_this();

	ii->getMouse()->onMove(self, [this](const glm::vec2 &delta) {

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

	ii->getMouse()->Left.onPressed(self, [&] {
		if (isMouseIn) onPressed();
	});

	ii->getMouse()->Left.onReleased(self, [&] {
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
	verticesBuf.emplace_back(point_xy, textureReference.getTexCoord_xy());
	verticesBuf.emplace_back(point_Xy, textureReference.getTexCoord_Xy());
	verticesBuf.emplace_back(point_XY, textureReference.getTexCoord_XY());
	verticesBuf.emplace_back(point_xY, textureReference.getTexCoord_xY());

	indicesBuf.clear();
	indicesBuf.emplace_back(0, 1, 2);
	indicesBuf.emplace_back(2, 3, 0);
}

gui::RectangleObj::~RectangleObj() {
	logger.log("~RectangleObj()");
}

const engine::SquareTextureReference &gui::RectangleObj::getTextureReference() const {
	return textureReference;
}

void gui::RectangleObj::setTextureReference(const engine::SquareTextureReference &textureReference) {
	RectangleObj::textureReference = textureReference;
	setNeedRefreshBuffers(true);
}

