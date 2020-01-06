//
// Created by adam on 07.11.2019.
//

#include "welcome.h"
#include "settings.h"
#include "worlds.h"

#include "src/game/gameScene.h"


menu::WelcomeScene::WelcomeScene() {}

menu::WelcomeScenePtr menu::WelcomeScene::create() {
	struct trick : public WelcomeScene {
	};
	auto self = std::make_shared<trick>();

	self->interface = std::make_shared<gui::Interface>();
	self->setInputInterface(self->interface->getInputInterface());

	self->playBtn = gui::Button::create(self->interface);
	self->playBtn->setPosition(glm::vec2(0, 0.3));
	self->playBtn->setText("Graj");

	self->settingsBtn = gui::Button::create(self->interface);
	self->settingsBtn->setPosition(glm::vec2(0, 0.5));
	self->settingsBtn->setText("Ustawienia");

	self->quitBtn = gui::Button::create(self->interface);
	self->quitBtn->setPosition(glm::vec2(0, 0.7));
	self->quitBtn->setText("Koniec");

	self->initBtnActions();

	return self;
}


void menu::WelcomeScene::initBtnActions() {
	playBtn->onClicked([&] {

		auto winWPtr = getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();

		auto newScene = game::GameScene::create();

		winPtr->setScene(newScene);
	});


	//	settingsBtn->onClicked([&] {
//		getWindow()->setScene(new SettingsScene);
//	});
}


void menu::WelcomeScene::render(engine::WindowPtr& window) {
	auto ptr = this->shared_from_this();
	interface->render(ptr);
}

menu::WelcomeScene::~WelcomeScene() {
	logger.log("usuwanie WelcomeScene");
}