//
// Created by adam on 16.10.2019.
//

#include "gamewin.h"
#include "gamescene.h"

void game::MainWindow::initObjects() {
	setScene(new GameScene);
}

std::string game::MainWindow::getTitle() {
	return "dupa";
}
