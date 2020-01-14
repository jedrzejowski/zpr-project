/**
 * @file Button.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Button.h"
#include "src/lib/Object.h"
#include "src/OpenGL.h"

gui::Button::Button(InterfacePtr &interface) : RectangleObj(interface) {}

gui::Button::Button(gui::GuiObjectPtr &gui_object) : RectangleObj(gui_object) {}

void gui::Button::constructorButton() {
	RectangleObj::constructorRectangleObj();

	text_size = 1;

	setState(Idle);

	onEnter([&] {
		if (state != Disabled)
			setState(Hover);
	});

	onLeave([&] {
		if (state != Disabled)
			setState(Idle);
	});

	onPressed([&] {
		if (state != Disabled)
			onClicked();
	});

	text = std::make_shared<Text>(this->shared_from_this());

	onSizeChanged([&](const glm::vec2 &old_size, const glm::vec2 &new_size) {
		setNeedRefreshBuffers(true);
	});

	text->onContentChanged([&](const std::string &old_content, const std::string &new_content) {
		setNeedRefreshBuffers(true);
	});
}

gui::ButtonPtr gui::Button::create(gui::InterfacePtr interface) {
	struct Self : Button {
		Self(InterfacePtr &interface) : Button(interface) {}
	};

	auto self = std::make_shared<Self>(interface);
	self->constructorButton();
	return self;
}

gui::ButtonPtr gui::Button::create(gui::GuiObjectPtr gui_object) {
	struct Self : Button {
		Self(GuiObjectPtr &gui_object) : Button(gui_object) {}
	};

	auto self = std::make_shared<Self>(gui_object);
	self->constructorButton();
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

const std::string &gui::Button::getText() const {
	return text->getContent();
}

void gui::Button::setText(const std::string &new_text) {
	text->setContent(new_text);
}

void gui::Button::updateTextModel() {
	auto model = glm::mat4(1);
	auto base_size = getBaseSize();

	auto text_factor = base_size.y * text_size / 2;

	model = glm::translate(model, glm::vec3(
			(base_size.x - text->getContentLength() * text_factor / getSize().x) / 2,
			(base_size.y - text_factor) / 2,
			-.1));

	model = glm::scale(model, glm::vec3(text_factor / getSize().x, text_factor, 1));

	text->setModel(model);
}

float gui::Button::getTextSize() const {
	return text_size;
}

void gui::Button::setTextSize(float new_size) {
	text_size = new_size;
	setNeedRefreshBuffers(true);
}

void gui::Button::updateBuffers() {
	updateTextModel();
	RectangleObj::updateBuffers();
}
