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

menu::WelcomeScene::~WelcomeScene() {
	logger(4).destructor(this);
}

menu::WelcomeScenePtr menu::WelcomeScene::create() {
	struct trick : public WelcomeScene {
	};
	auto self = std::make_shared<trick>();

	self->interface = std::make_shared<gui::Interface>();
	self->setInputInterface(self->interface->getInputInterface());

	self->play_button = gui::Button::create(self->interface);
	self->play_button->setPosition(glm::vec2(0, 0.3));
	self->play_button->setText("Graj");

	self->settings_button = gui::Button::create(self->interface);
	self->settings_button->setPosition(glm::vec2(0, 0.5));
	self->settings_button->setText("Ustawienia");

	self->quit_button = gui::Button::create(self->interface);
	self->quit_button->setPosition(glm::vec2(0, 0.7));
	self->quit_button->setText("Koniec");

	self->initEvents();

	return self;
}


void menu::WelcomeScene::initEvents() {
	play_button->onClicked([&] {

		auto winWPtr = getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();

		auto newScene = game::GameScene::create();

		winPtr->setScene(newScene);
	});


	settings_button->onClicked([&] {
//		getWindow()->setScene(new SettingsScene);
	});

	quit_button->onClicked([&] {
		if (auto window_ptr = getWindow().lock())
			window_ptr->close();
	});
}


void menu::WelcomeScene::render(engine::WindowPtr &window) {
	auto ptr = this->shared_from_this();
	interface->render(ptr);
}