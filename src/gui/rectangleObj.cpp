#include "rectangleObj.h"
#include "interface.h"

gui::RectangleObj::RectangleObj(Interface *interface) :
		GuiObject(interface) {
}

void gui::RectangleObj::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
										std::vector<engine::SimpleTriangle> &indices) {

	auto offset = vertices.size();

	auto recModel = glm::mat4(1);
	recModel = glm::translate(recModel, position);
	recModel = glm::scale(recModel, size);

	point_xy = getModel() * recModel * glm::vec4(0, 0, 0, 1);
	point_Xy = getModel() * recModel * glm::vec4(1, 0, 0, 1);
	point_XY = getModel() * recModel * glm::vec4(1, 1, 0, 1);
	point_xY = getModel() * recModel * glm::vec4(0, 1, 0, 1);

	vertices.emplace_back(point_xy, engine::TexCoord(textureStart.x, textureStart.y));
	vertices.emplace_back(point_Xy, engine::TexCoord(textureEnd.x, textureStart.y));
	vertices.emplace_back(point_XY, engine::TexCoord(textureEnd.x, textureEnd.y));
	vertices.emplace_back(point_xY, engine::TexCoord(textureStart.x, textureEnd.y));

	indices.push_back(engine::SimpleTriangle(0, 1, 2) + offset);
	indices.push_back(engine::SimpleTriangle(2, 3, 0) + offset);
}

bool gui::RectangleObj::isCollisionWithMouse(const engine::Mouse *mouse) {

	auto window = getInterface()->getScene()->getWindow();
	if (window == nullptr) return false;

	auto position = window->scalePixelPosToViewPortPos(engine::ViewPort::Square, mouse->getCurrentPosition());

	return point_xy.x < position.x && position.x < point_XY.x &&
		   point_xy.y < position.y && position.y < point_XY.y;
}

const glm::vec3 &gui::RectangleObj::getPosition() const {
	return position;
}

void gui::RectangleObj::setPosition(const glm::vec3 &position) {
	RectangleObj::position = position;
}

const glm::vec3 &gui::RectangleObj::getSize() const {
	return size;
}

void gui::RectangleObj::setSize(const glm::vec3 &size) {
	RectangleObj::size = size;
}

const glm::vec2 &gui::RectangleObj::getTextureStart() const {
	return textureStart;
}

void gui::RectangleObj::setTextureStart(const glm::vec2 &textureStart) {
	RectangleObj::textureStart = textureStart;

	getInterface()->setNeedRefreshBuffers(true);
}

const glm::vec2 &gui::RectangleObj::getTextureEnd() const {
	return textureEnd;
}

void gui::RectangleObj::setTextureEnd(const glm::vec2 &textureEnd) {
	RectangleObj::textureEnd = textureEnd;
}

void gui::RectangleObj::setTexture(const glm::vec2 &textureStart, const glm::vec2 &textureEnd) {
	setTextureStart(textureStart);
	setTextureEnd(textureEnd);

}

