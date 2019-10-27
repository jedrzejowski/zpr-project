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

	addObject(glm::vec2(0, 0.2), glm::vec2(1), resumeBtn);
	addObject(glm::vec2(0, 0.4), glm::vec2(1), optionsBtn);
	addObject(glm::vec2(0, 0.6), glm::vec2(1), saveBtn);

	getInputInterface()->getKeyboard().Escape.onPressed([&] {
		onMenuExit();
	});
}
