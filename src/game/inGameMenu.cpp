//
// Created by adam on 24.10.2019.
//

#include "inGameMenu.h"
#include "gameScene.h"

game::InGameMenu::InGameMenu(game::GameSceneWPtr scene) :
		Interface() {

	resumeBtn = std::make_shared<gui::Button>(this->shared_from_this());
	resumeBtn->setText("Wznow gre");
	resumeBtn->setPosition(glm::vec2(0, 0.3));
	resumeBtn->onClicked([&] {
		onMenuExit();
	});

	saveBtn = std::make_shared<gui::Button>(this->shared_from_this());
	saveBtn->setText("Zapisz i wyjdz");
	saveBtn->setPosition(glm::vec2(0, 0.5));
	saveBtn->onClicked([&] {
		onSaveAndExit();
	});

	getInputInterface()->getKeyboard()->Escape.onPressed([&] {
		onMenuExit();
	});
}
