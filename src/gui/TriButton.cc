/**
 * @file TriButton.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "TriButton.h"
#include "Button.h"


gui::TriButton::TriButton(gui::InterfacePtr &interface) : GuiObject(interface) {
	logger(4).constructor(this);
}

gui::TriButton::TriButton(gui::GuiObjectPtr &parent) : GuiObject(parent) {
	logger(4).constructor(this);
}

void gui::TriButton::constructorTriButton() {
	auto self = this->shared_from_this();

	negative_button_ptr = Button::create(self);
	negative_button_ptr->onClicked([&] { onNegativeClick(); });

	main_button_ptr = Button::create(self);
	main_button_ptr->onClicked([&] { onMainClick(); });

	positive_button_ptr = Button::create(self);
	positive_button_ptr->onClicked([&] { onPositiveClick(); });

}

gui::TriButton::~TriButton() {
	logger(4).destructor(this);
}

gui::TriButtonPtr gui::TriButton::create(gui::InterfacePtr &interface) {
	struct Self : TriButton {
		Self(gui::InterfacePtr &interface) : TriButton(interface) {}
	};

	TriButtonPtr self = std::make_shared<Self>(interface);
	self->constructorTriButton();
	return self;
}

gui::TriButtonPtr gui::TriButton::create(gui::GuiObjectPtr &parent) {
	struct Self : TriButton {
		Self(gui::GuiObjectPtr &parent) : TriButton(parent) {}
	};

	TriButtonPtr self = std::make_shared<Self>(parent);
	self->constructorTriButton();
	return self;
}


void gui::TriButton::updateBuffers() {
	setNeedRefreshBuffers(false);
}

const glm::vec2 &gui::TriButton::getPosition() const {
	return position;
}

void gui::TriButton::setPosition(const glm::vec2 &new_position) {
	position = new_position;
	updateModel();
}

const glm::vec2 &gui::TriButton::getSize() const {
	return size;
}

void gui::TriButton::setSize(const glm::vec2 &new_size) {
	size = new_size;
	updateModel();
}

void gui::TriButton::updateModel() {

	auto base_size = glm::vec2(1, 0.13);

	auto padding = base_size.y * 0.05;
	auto padding_vec = glm::vec2(padding, 0);

	auto positive_size = glm::vec2(base_size.y, 1);
	auto negative_size = glm::vec2(base_size.y, 1);
	auto main_size = glm::vec2(1, 1)
					 - padding_vec - glm::vec2(negative_size.x, 0)
					 - padding_vec - glm::vec2(positive_size.x, 0);

	negative_button_ptr->setSize(negative_size);
	main_button_ptr->setSize(main_size);
	positive_button_ptr->setSize(positive_size);

	negative_button_ptr->setPosition(glm::vec2(0));
	main_button_ptr->setPosition(
			negative_button_ptr->getPosition() +
			glm::vec2(negative_button_ptr->getSize().x, 0) +
			padding_vec);
	positive_button_ptr->setPosition(
			main_button_ptr->getPosition() +
			glm::vec2(main_button_ptr->getSize().x, 0) +
			padding_vec);


	auto recModel = glm::mat4(1);
	recModel = glm::translate(recModel, glm::vec3(position, 0));
	recModel = glm::scale(recModel, glm::vec3(size, 1));
	setModel(recModel);
}

const gui::ButtonPtr &gui::TriButton::getMainButton() const {
	return main_button_ptr;
}

const gui::ButtonPtr &gui::TriButton::getPositiveButton() const {
	return positive_button_ptr;
}

const gui::ButtonPtr &gui::TriButton::getNegativeButton() const {
	return negative_button_ptr;
}

void gui::TriButton::setText(const std::string &negative_text,
							 const std::string &main_text,
							 const std::string &positive_text) {
	negative_button_ptr->setText(negative_text);
	main_button_ptr->setText(main_text);
	positive_button_ptr->setText(positive_text);
}
