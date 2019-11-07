//
// Created by adam on 16.10.2019.
//

#include "mainWin.h"
#include "src/game/Game.h"
#include "src/menu/Menu.h"

void MainWindow::initObjects() {
//	auto scene = new game::GameScene;
	auto scene = new menu::MainMenu;
	setScene(scene);
}

std::string MainWindow::getTitle() {
	return "ZprCraft";
}
