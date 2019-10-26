#include "guiObj.h"
#include "interface.h"

gui::GuiObject::GuiObject(Object *parent) : Object(parent) {
}


void gui::GuiObject::insertSquareToBuffers(
		float x, float y, float width, float height,
		float textureX, float textureY,
		float textureWidth, float textureHeight,
		std::vector<engine::Point3DeX> &vertices,
		std::vector<engine::SimpleTriangle> &indices) {

	auto offset = vertices.size();

	vertices.emplace_back(
			model * glm::vec4(x, y, 0.f, 1.f),
			engine::TexCoord(textureX, textureY));
	vertices.emplace_back(
			model * glm::vec4(x + width, y, 0.f, 1.f),
			engine::TexCoord(textureX + textureWidth, textureY));
	vertices.emplace_back(
			model * glm::vec4(x + width, y + height, 0.f, 1.f),
			engine::TexCoord(textureX + textureWidth, textureY + textureHeight));
	vertices.emplace_back(
			model * glm::vec4(x, y + height, 0.f, 1.f),
			engine::TexCoord(textureX, textureY + textureHeight));

	indices.push_back(engine::SimpleTriangle(0, 1, 2) + offset);
	indices.push_back(engine::SimpleTriangle(2, 3, 0) + offset);
}

const glm::mat4 &gui::GuiObject::getModel() const {
	return model;
}

void gui::GuiObject::setModel(const glm::mat4 &model) {
	GuiObject::model = model;
}
