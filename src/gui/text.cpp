
#include "text.h"

gui::Text::Text(Object *parent) : Object(parent) {
}

const glm::mat4 &gui::Text::getModel() const {
	return model;
}

void gui::Text::setModel(const glm::mat4 &model) {
	this->model = model;
}

const std::string &gui::Text::getContent() const {
	return content;
}

void gui::Text::setContent(const std::string &content) {
	Text::content = content;
}
