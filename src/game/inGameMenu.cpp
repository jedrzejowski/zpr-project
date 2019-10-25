//
// Created by adam on 24.10.2019.
//

#include "inGameMenu.h"
#include "gameScene.h"

game::InGameMenu::InGameMenu(game::GameScene *scene) :
		Interface(scene) {


	button = new gui::Button();
	addObject(glm::vec3(0, 0, 0), button);

	refreshBuffers();
}