#include "button.h"
#include "src/lib/object.h"

gui::Button::Button(InterfacePtr interface) :
		RectangleObj(interface) {
	setState(Idle);

	onEnter([&] {
		setState(Hover);
	});

	onLeave([&] {
		setState(Idle);
	});

	onPressed([&] {
		onClicked();
	});
}

gui::ButtonState gui::Button::getState() const {
	return state;
}

void gui::Button::setState(gui::ButtonState state) {
	Button::state = state;

	switch (state) {
		case Idle:
			setTexture(
					glm::vec2(0, 1 / 3.f),
					glm::vec2(1, 2 / 3.f)
			);
			break;
		case Hover:
			setTexture(
					glm::vec2(0, 2 / 3.f),
					glm::vec2(1, 1)
			);
			break;
		case Clicked:
			setTexture(
					glm::vec2(0, 0),
					glm::vec2(1, 1 / 3.f)
			);
			break;
		case Disabled:
			setTexture(
					glm::vec2(0, 0),
					glm::vec2(1, 1 / 3.f)
			);
			break;
	}
}

glm::vec2 gui::Button::getBaseSize() {
	return glm::vec2(1, 0.13);
}

void gui::Button::initText() {
	if (text != nullptr)
		return;

	auto t = this->shared_from_this();
	text = std::make_shared<Text>(t);
	auto model = text->getModel();
	model = glm::translate(model, glm::vec3(0, 0.13 / 4, -.1));
	model = glm::scale(model, glm::vec3(0.13 / 2, 0.13 / 2, 1));
	text->setModel(model);
}


const std::string &gui::Button::getText() {
	initText();
	return text->getContent();
}

void gui::Button::setText(const std::string &text) {
	initText();
	this->text->setContent(text);
}