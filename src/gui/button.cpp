#include "button.h"
#include "src/lib/object.h"

gui::Button::Button(InterfacePtr &interface) :
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

gui::ButtonPtr gui::Button::create(gui::InterfacePtr interface) {
	struct trick : Button {
		trick(InterfacePtr &interface) : Button(interface) {}
	};

	auto self = std::make_shared<trick>(interface);
	self->initInputInterface();

	self->text = std::make_shared<Text>(self);
	auto model = self->text->getModel();
	model = glm::translate(model, glm::vec3(0, 0.13 / 4, -.1));
	model = glm::scale(model, glm::vec3(0.13 / 2, 0.13 / 2, 1));
	self->text->setModel(model);

	return self;
}

gui::ButtonState gui::Button::getState() const {
	return state;
}

void gui::Button::setState(gui::ButtonState state) {
	Button::state = state;

	switch (state) {
		case Idle:
			setTextureReference(
					engine::SquareTextureReference(
							glm::vec2(0, 1 / 3.f),
							glm::vec2(1, 2 / 3.f),
							global::TextureGuiNo
					)
			);
			break;
		case Hover:
			setTextureReference(
					engine::SquareTextureReference(
							glm::vec2(0, 2 / 3.f),
							glm::vec2(1, 1),
							global::TextureGuiNo
					)
			);
			break;
		case Clicked:
			setTextureReference(
					engine::SquareTextureReference(
							glm::vec2(0, 0),
							glm::vec2(1, 1 / 3.f),
							global::TextureGuiNo
					)
			);
			break;
		case Disabled:
			setTextureReference(
					engine::SquareTextureReference(
							glm::vec2(0, 0),
							glm::vec2(1, 1 / 3.f),
							global::TextureGuiNo
					)
			);
			break;
	}
}

glm::vec2 gui::Button::getBaseSize() {
	return glm::vec2(1, 0.13);
}

const std::string &gui::Button::getText() {
	return text->getContent();
}

void gui::Button::setText(const std::string &text) {
	this->text->setContent(text);
}
