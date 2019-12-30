
#include "text.h"

gui::Text::Text(gui::InterfacePtr interface) :
		GuiObject(interface) {
}

gui::Text::Text(gui::GuiObjectPtr parent) :
		GuiObject(parent) {
}

const std::string &gui::Text::getContent() const {
	return content;
}

void gui::Text::setContent(const std::string &content) {
	Text::content = content;
	setNeedRefreshBuffers(true);
}

void gui::Text::updateBuffers() {

	verticesBuf.clear();
	indicesBuf.clear();

	int offset = 0;
	int charInd = 0;

	for (auto c : content) {
		int x = (int) c % 16;
		int y = (int) c / 16;

		glm::vec4 point_xy = getModel() * glm::vec4(0 + charInd, 0, 0, 1);
		glm::vec4 point_Xy = getModel() * glm::vec4(1 + charInd, 0, 0, 1);
		glm::vec4 point_XY = getModel() * glm::vec4(1 + charInd, 1, 0, 1);
		glm::vec4 point_xY = getModel() * glm::vec4(0 + charInd, 1, 0, 1);

		verticesBuf.emplace_back(point_xy, engine::TexCoord((float) x / 16, (float) y / 16, 1));
		verticesBuf.emplace_back(point_Xy, engine::TexCoord((float) (x + 1) / 16, (float) y / 16, 1));
		verticesBuf.emplace_back(point_XY, engine::TexCoord((float) (x + 1) / 16, (float) (y + 1) / 16, 1));
		verticesBuf.emplace_back(point_xY, engine::TexCoord((float) x / 16, (float) (y + 1) / 16, 1));

		indicesBuf.push_back(engine::SimpleTriangle(0, 1, 2) + offset);
		indicesBuf.push_back(engine::SimpleTriangle(2, 3, 0) + offset);

		offset += 4;
		charInd++;
	}
}
