//
// Created by adam on 16.10.2019.
//

#include <src/logger.h>
#include "gameScene.h"
#include "player.h"
#include "inGameMenu.h"

game::GameScene::GameScene() {
	worldMap = new map::WorldMap();

	player = new Player();
	player->setParent(this);

	mapRenderer = new map::Renderer(this, player, worldMap);
	mapRenderer->setParent(this);

	initGameEvents();
	inGameMenu = new InGameMenu(this);

	setInterfaceState(Game);
}

void game::GameScene::render3D(engine::Window *window) {
	mapRenderer->render(this);
}

void game::GameScene::renderGUI(engine::Window *window) {
	if (interfaceState == Menu)
		inGameMenu->render(this);
}

void game::GameScene::initGameEvents() {

	auto &keyboard = gameInput.getKeyboard();
	auto &mouse = gameInput.getMouse();

	mouse.setAttachedToCenter(true);

	keyboard.W.onPress.connect([&] {
		player->moveForward(keyboard.getDeltaTimeOfState());
	});

	keyboard.S.onPress.connect([&] {
		player->moveBackward(keyboard.getDeltaTimeOfState());
	});

	keyboard.D.onPress.connect([&] {
		player->moveRight(keyboard.getDeltaTimeOfState());
	});

	keyboard.A.onPress.connect([&] {
		player->moveLeft(keyboard.getDeltaTimeOfState());
	});

	keyboard.Space.onPress.connect([&] {
		player->moveUp(keyboard.getDeltaTimeOfState());
	});

	keyboard.LShift.onPress.connect([&] {
		player->moveDown(keyboard.getDeltaTimeOfState());
	});

	keyboard.Escape.onPressed.connect([&] {
		setInterfaceState(Menu);
	});

	mouse.onMove.connect([&](double dx, double dy) {
		player->rotateRight(dx);
		player->rotateDown(dy);
	});
}

game::GameSceneState game::GameScene::getInterfaceState() const {
	return interfaceState;
}

void game::GameScene::setInterfaceState(game::GameSceneState interfaceState) {
	GameScene::interfaceState = interfaceState;

	switch (interfaceState) {
		case Game:
			setInputInterface(&gameInput);
			break;
		case Menu:
			setInputInterface(inGameMenu->getInputInterface());
			break;
	}
}
