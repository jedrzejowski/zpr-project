/**
 * @file Text.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */


#include "Text.h"

gui::Text::Text(gui::InterfacePtr interface) :
		GuiObject(interface) {
}

gui::Text::Text(gui::GuiObjectPtr parent) :
		GuiObject(parent) {
}

const std::string &gui::Text::getContent() const {
	return content;
}

void gui::Text::setContent(const std::string &new_content) {
	auto old_content = content;
	content = new_content;
	setNeedRefreshBuffers(true);
	onContentChanged(old_content, new_content);
}

void gui::Text::updateBuffers() {

	vertices_buffer.clear();
	indices_buffer.clear();

	int offset = 0;
	int charInd = 0;

	for (auto c : content) {
		int x = (int) c % 16;
		int y = (int) c / 16;

		glm::vec4 point_xy = getModel() * glm::vec4(0 + charInd, 0, 0, 1);
		glm::vec4 point_Xy = getModel() * glm::vec4(1 + charInd, 0, 0, 1);
		glm::vec4 point_XY = getModel() * glm::vec4(1 + charInd, 1, 0, 1);
		glm::vec4 point_xY = getModel() * glm::vec4(0 + charInd, 1, 0, 1);

		vertices_buffer.emplace_back(point_xy,
									 engine::TexCoord((float) x / 16, (float) y / 16, global::TextureFontNo));
		vertices_buffer.emplace_back(point_Xy,
									 engine::TexCoord((float) (x + 1) / 16, (float) y / 16, global::TextureFontNo));
		vertices_buffer.emplace_back(point_XY,
									 engine::TexCoord((float) (x + 1) / 16, (float) (y + 1) / 16,
													  global::TextureFontNo));
		vertices_buffer.emplace_back(point_xY,
									 engine::TexCoord((float) x / 16, (float) (y + 1) / 16, global::TextureFontNo));

		indices_buffer.push_back(engine::EboTriangle(0, 1, 2) + offset);
		indices_buffer.push_back(engine::EboTriangle(2, 3, 0) + offset);

		offset += 4;
		++charInd;
	}

	setNeedRefreshBuffers(false);
}

float gui::Text::getContentLength() const {
	return content.length();
}
