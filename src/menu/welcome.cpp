//
// Created by adam on 07.11.2019.
//

#include "welcome.h"
#include "settings.h"
#include "worlds.h"

#include "src/game/gameScene.h"


menu::WelcomeScene::WelcomeScene() {

	interface = std::make_shared<gui::Interface>();
	setInputInterface(interface->getInputInterface());

	worldsBtn = std::make_shared<gui::Button>(interface);
	worldsBtn->setPosition(glm::vec2(0, 0.3));
	worldsBtn->setText("Graj");

	settingsBtn = std::make_shared<gui::Button>(interface);
	settingsBtn->setPosition(glm::vec2(0, 0.5));
	settingsBtn->setText("Ustawienia");

	quitBtn = std::make_shared<gui::Button>(interface);
	quitBtn->setPosition(glm::vec2(0, 0.7));
	quitBtn->setText("Koniec");

	worldsBtn->onClicked([&] {

		auto winWPtr = getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();

		auto newScene = std::make_shared<game::GameScene>();

		winPtr->setScene(newScene);
	});

//	settingsBtn->onClicked([&] {
//		getWindow()->setScene(new SettingsScene);
//	});
}

void menu::WelcomeScene::render(engine::WindowPtr window) {
	auto ptr = this->shared_from_this();
	interface->render(ptr);
}
menu::WelcomeScene::~WelcomeScene() {
	logger.log("usuwanie WelcomeScene");
}
