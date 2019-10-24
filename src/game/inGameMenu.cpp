//
// Created by adam on 24.10.2019.
//

#include "inGameMenu.h"
#include "gameScene.h"

game::InGameMenu::InGameMenu(game::GameScene *scene) : Abs3DObj() {

	shader = new engine::Shader("shader/interface.vert", "shader/interface.frag");
	button = new gui::Button();
}

void game::InGameMenu::render(engine::Scene *scene) {
	shader->bind();

	button->render(scene);
}
