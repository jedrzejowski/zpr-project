//
// Created by adam on 07.11.2019.
//

#include "welcome.h"
#include "settings.h"
#include "worlds.h"

#include "src/game/gameScene.h"


menu::WelcomeScene::WelcomeScene() {
	interface = new gui::Interface(this);
	setInputInterface(interface->getInputInterface());

	worldsBtn = new gui::Button(interface);
	worldsBtn->setPosition(glm::vec2(0, 0.3));
	worldsBtn->setText("Graj");

	settingsBtn = new gui::Button(interface);
	settingsBtn->setPosition(glm::vec2(0, 0.5));
	settingsBtn->setText("Ustawienia");

	quitBtn = new gui::Button(interface);
	quitBtn->setPosition(glm::vec2(0, 0.7));
	quitBtn->setText("Koniec");

	worldsBtn->onClicked([&] {
		getWindow()->setScene(new game::GameScene);
	});

	settingsBtn->onClicked([&] {
		getWindow()->setScene(new SettingsScene);
	});
}

void menu::WelcomeScene::render(engine::Window *window) {
	interface->render(this);
}
