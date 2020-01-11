/**
 * @file WelcomeScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WelcomeScene.h"
#include "SettingsScene.h"
#include "WorldsScene.h"

#include "src/game/GameScene.h"


menu::WelcomeScene::WelcomeScene() {
	logger(4).constructor(this);
}

void menu::WelcomeScene::constructorWelcomeScene() {
	interface = std::make_shared<gui::Interface>();
	setInputInterface(interface->getInputInterface());

	play_button = gui::Button::create(interface);
	play_button->setPosition(glm::vec2(0, 0.3));
	play_button->setText("Graj");
	play_button->onClicked([&] {

		if (auto window_ptr = getWindow().lock()) {

			auto newScene = game::GameScene::create();
			window_ptr->setScene(newScene);
		}
	});

	settings_button = gui::Button::create(interface);
	settings_button->setPosition(glm::vec2(0, 0.5));
	settings_button->setText("Ustawienia");
	settings_button->onClicked([&] {
		if (auto window_ptr = getWindow().lock()) {

			auto newScene = menu::SettingsScene::create();
			window_ptr->setScene(newScene);
		}
	});

	quit_button = gui::Button::create(interface);
	quit_button->setPosition(glm::vec2(0, 0.7));
	quit_button->setText("Koniec");
	quit_button->onClicked([&] {
		if (auto window_ptr = getWindow().lock())
			window_ptr->close();
	});
}

menu::WelcomeScene::~WelcomeScene() {
	logger(4).destructor(this);
}

menu::WelcomeScenePtr menu::WelcomeScene::create() {
	struct Self : public WelcomeScene {
	};
	auto self = std::make_shared<Self>();

	self->constructorWelcomeScene();

	return self;
}


void menu::WelcomeScene::render(engine::WindowPtr &window) {
	interface->render(this->shared_from_this());
}