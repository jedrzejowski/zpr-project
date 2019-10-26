//
// Created by adam on 24.10.2019.
//

#include "inGameMenu.h"
#include "gameScene.h"

game::InGameMenu::InGameMenu(game::GameScene *scene) :
		Interface(scene) {


	resumeBtn = new gui::Button(this);
	optionsBtn = new gui::Button(this);
	saveBtn = new gui::Button(this);

	float btnWidth = 0.13;
	addObject(glm::vec2(0, 0.5 - btnWidth * 2), glm::vec2(1, btnWidth), resumeBtn);
	addObject(glm::vec2(0, 0.5 - btnWidth / 2), glm::vec2(1, btnWidth), optionsBtn);
	addObject(glm::vec2(0, 0.5 + btnWidth), glm::vec2(1, btnWidth), saveBtn);

	initInputInterface();
}

engine::InputInterface *game::InGameMenu::getInputInterface() const {
	return inputInterface;
}

void game::InGameMenu::initInputInterface() {
	inputInterface = new engine::InputInterface(this);

	auto &keyboard = inputInterface->getKeyboard();
	auto &mouse = inputInterface->getMouse();

	keyboard.Escape.onPressed([&] {
		onMenuExit();
	});
}

