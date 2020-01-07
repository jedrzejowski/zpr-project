/**
 * @file MainWindow.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "MainWindow.h"
#include "src/game/Game.h"
#include "src/menu/Menu.h"

void MainWindow::initObjects() {
//	auto scene = new game::GameScene;
	auto scene = menu::WelcomeScene::create();
	setScene(scene);
}

std::string MainWindow::getTitle() {
	return "ZprCraft";
}
