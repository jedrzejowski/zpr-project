//
// Created by adam on 24.10.2019.
//

#include "inGameMenu.h"
#include "gameScene.h"

game::InGameMenu::InGameMenu(game::GameScene *scene) :
		Interface(scene) {

	resumeBtn = new gui::Button(this);
	resumeBtn->setPosition(glm::vec2(0, 0.2));
	optionsBtn = new gui::Button(this);
	optionsBtn->setPosition(glm::vec2(0, 0.4));
	saveBtn = new gui::Button(this);
	saveBtn->setPosition(glm::vec2(0, 0.6));

	getInputInterface()->getKeyboard()->Escape.onPressed([&] {
		onMenuExit();
	});
}
