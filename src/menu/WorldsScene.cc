/**
 * @file WorldsScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldsScene.h"
#include "WelcomeScene.h"
#include "src/gui/Interface.h"
#include "src/map/World.h"
#include "src/map/WorldManager.h"
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

	// iterowanie po światach
	for (const auto &code_name : map::WorldManager::get().getAllCodeNames())
		newWorldButton(code_name);

	add_button = gui::Button::create(interface);
	add_button->setText("Nowy swiat");
	add_button->onClicked([&] {
		auto new_world=map::WorldManager::get().newWorld();
		openWorld(new_world->getCodeName());
	});

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
	auto world_ptr = map::WorldManager::get().openWorld(code_name);

	auto button = gui::TriButton::create(interface);
	worlds_button.push_back(button);

	button->setText("X", world_ptr->getDisplayName(), "R");

	button->onMainClick([&, code_name] { openWorld(code_name); });

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

void menu::WorldsScene::pollEvents() {

	// scrolling
	if (auto window_ptr = getWindow().lock()) {
		static auto scroll_threshold = 0.2f, speed_ratio = 1.0f;

		auto mouse = getInputInterface()->getMouse();

		if (mouse->isInWindow()) {

			auto mouse_pos = mouse->getCurrentPosition();
			auto win_height = float(window_ptr->getWinHeight());
			auto time = float(mouse->getDeltaTimeOfState());

			if (mouse_pos.y <= scroll_threshold * win_height) {

				scroll_offset -= speed_ratio * time;
				updateButtonsPositions();
			} else if (mouse_pos.y >= (1 - scroll_threshold) * win_height) {

				scroll_offset += speed_ratio * time;
				updateButtonsPositions();
			}
		}
	}
}

void menu::WorldsScene::openWorld(const std::string &code_name) {
	if (auto window_ptr = getWindow().lock()) {
		auto newScene = game::GameScene::create(code_name);
		window_ptr->setScene(newScene);
	}
}
