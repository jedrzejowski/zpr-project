
#include "text.h"

gui::Text::Text(gui::Interface *interface) :
		GuiObject(interface) {
}

gui::Text::Text(gui::GuiObject *parent) :
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
	auto recModel = glm::mat4(1);

	verticesBuf.clear();
	indicesBuf.clear();
	return;
	float x = 0;
	int offset = 0;

	for (auto c : content) {
		int x = c % 16;
		int y = c / 16;

		verticesBuf.emplace_back(0, 0, 0, engine::TexCoord(0, 0, 1));
		verticesBuf.emplace_back(1, 0, 0, engine::TexCoord(1, 0, 1));
		verticesBuf.emplace_back(1, 1, 0, engine::TexCoord(1, 1, 1));
		verticesBuf.emplace_back(0, 1, 0, engine::TexCoord(0, 1, 1));
		logger.log(c);

		indicesBuf.push_back(engine::SimpleTriangle(0, 1, 2) + offset);
		indicesBuf.push_back(engine::SimpleTriangle(2, 3, 0) + offset);
		offset += 4;
	}

//	verticesBuf.emplace_back(point_xy, engine::TexCoord(textureStart.x, textureStart.y));
//	verticesBuf.emplace_back(point_Xy, engine::TexCoord(textureEnd.x, textureStart.y));
//	verticesBuf.emplace_back(point_XY, engine::TexCoord(textureEnd.x, textureEnd.y));
//	verticesBuf.emplace_back(point_xY, engine::TexCoord(textureStart.x, textureEnd.y));
//
//	indicesBuf.emplace_back(0, 1, 2);
//	indicesBuf.emplace_back(2, 3, 0);

}
