//
// Created by adam on 16.10.2019.
//

#include "gamewin.h"
#include "gamescene.h"

void GameWin::initObjects() {
	setScene(new GameScene);
}

std::string GameWin::getTitle() {
	return "dupa";
}
