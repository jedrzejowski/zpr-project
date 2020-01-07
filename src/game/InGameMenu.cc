//
// Created by adam on 24.10.2019.
//

#include "InGameMenu.h"
#include "GameScene.h"

game::InGameMenu::InGameMenu(game::GameScenePtr &scene) :
		Interface() {


	getInputInterface()->getKeyboard()->Escape.onPressed([&] {
		onMenuExit();
	});
}

game::InGameMenuPtr game::InGameMenu::create(game::GameScenePtr &scene) {
	struct trick : InGameMenu {
		trick(game::GameScenePtr &scene) : InGameMenu(scene) {}
	};

	InGameMenuPtr self = std::make_shared<trick>(scene);
	self->initEvents();

	return self;
}

void game::InGameMenu::initEvents() {
	resumeBtn = gui::Button::create(this->shared_from_this());
	resumeBtn->setText("Wznow gre");
	resumeBtn->setPosition(glm::vec2(0, 0.3));
	resumeBtn->onClicked([&] {
		onMenuExit();
	});

	saveBtn = gui::Button::create(this->shared_from_this());
	saveBtn->setText("Zapisz i wyjdz");
	saveBtn->setPosition(glm::vec2(0, 0.5));
	saveBtn->onClicked([&] {
		onSaveAndExit();
	});
}
