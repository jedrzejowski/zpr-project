/**
 * @file WorldsScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldsScene.h"
#include "WelcomeScene.h"
#include "src/gui/Interface.h"
#include "src/map/World.h"
#include "src/gui/TriButton.h"
#include "src/game/GameScene.h"


menu::WorldsScene::WorldsScene() {
	logger(4).constructor(this);
}

void menu::WorldsScene::constructorWorldsScene() {
	interface = std::make_shared<gui::Interface>();
	auto input_interface = interface->getInputInterface();
	setInputInterface(interface->getInputInterface());

	input_interface->getKeyboard()->Escape.onPressed([&] { backToWelcomeScene(); });

	// scrolling
	input_interface->getMouse()->onMove([&](const glm::vec2 &delta) {
		updateButtonsPositions();
	});

	// iterowanie po światach
	for (auto iterator = boost::filesystem::directory_iterator(map::World::getBaseDirectory());
		 iterator != boost::filesystem::directory_iterator{}; iterator++) {

		auto code_name = iterator->path().leaf().string();
		newWorldButton(code_name);
	}

	add_button = gui::Button::create(interface);
	add_button->setText("Nowy swiat");
	add_button->onClicked([&] { initNewWorld(); });

	return_button = gui::Button::create(interface);
	return_button->setText("Wroc");
	return_button->onClicked([&] { backToWelcomeScene(); });


	updateButtonsPositions();
}

menu::WorldsScene::~WorldsScene() {
	logger(4).destructor(this);
}

menu::WorldsScenePtr menu::WorldsScene::create() {
	struct Self : public WorldsScene {
	};

	WorldsScenePtr self = std::make_shared<Self>();
	self->constructorWorldsScene();
	return self;
}

void menu::WorldsScene::render(engine::WindowPtr &window) {
	interface->render(this->shared_from_this());
}

void menu::WorldsScene::newWorldButton(const std::string &code_name) {
	auto world_ptr = map::World::create(code_name);

	auto button = gui::TriButton::create(interface);
	worlds_button.push_back(button);

	button->setText("X", world_ptr->getDisplayName(), "R");

	button->onMainClick([&, code_name] {
		if (auto window_ptr = getWindow().lock()) {
			auto newScene = game::GameScene::create(code_name);
			window_ptr->setScene(newScene);
		}
	});

	button->onPositiveClick([&] {
	});

	button->onNegativeClick([&] {
	});
}

void menu::WorldsScene::backToWelcomeScene() {
	if (auto window_ptr = getWindow().lock()) {
		auto newScene = menu::WelcomeScene::create();
		window_ptr->setScene(newScene);
	}
}

void menu::WorldsScene::updateButtonsPositions() {
	float padding = 0.2;

	float full_width = 0.1f + worlds_button.size() * padding + padding * 3;

	if (scroll_offset < 0) scroll_offset = 0;
	if (scroll_offset > full_width - 1) scroll_offset = full_width - 1;

	float new_settings_position = 0.1f - scroll_offset;

	for (const auto &it : worlds_button) {
		it->setPosition(glm::vec2(0, new_settings_position));
		new_settings_position += padding;
	}

	add_button->setPosition(glm::vec2(0, new_settings_position));

	new_settings_position += padding;

	return_button->setPosition(glm::vec2(0, new_settings_position));
}

void menu::WorldsScene::initNewWorld() {
}

void menu::WorldsScene::pollEvents() {

	// scrolling
	if (auto window_ptr = getWindow().lock()) {
		static auto scroll_threshold = 0.2f, speed_ratio = 1.0f;

		auto mouse = getInputInterface()->getMouse();

		if (mouse->isInWindow()) {

			auto mouse_pos = mouse->getCurrentPosition();

			if (mouse_pos.y <= scroll_threshold * window_ptr->getWinHeight()) {
				scroll_offset -= speed_ratio * mouse->getDeltaTimeOfState();
				updateButtonsPositions();
			}

			if (mouse_pos.y >= (1 - scroll_threshold) * window_ptr->getWinHeight()) {
				scroll_offset += speed_ratio * mouse->getDeltaTimeOfState();
				updateButtonsPositions();
			}
		}
	}
}
