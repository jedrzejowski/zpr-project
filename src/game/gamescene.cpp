//
// Created by adam on 16.10.2019.
//

#include <src/logger.h>
#include "gamescene.h"
#include "player.h"

game::GameScene::GameScene() {
	worldMap = new map::WorldMap();
	worldMap->setChunk(0, 0, new map::Chunk());

	player = new Player();
	player->setParent(this);

	mapRenderer = new map::Renderer(this, player, worldMap);
	mapRenderer->setParent(this);

	initKeyboardEvents();
	setKeyboard(&gameKeyboard);

	mouse.setAttachedToCenter(true);
	initMouseEvents();
	setMouse(&mouse);
}

void game::GameScene::render3D(engine::Window *window) {
	mapRenderer->render(this);
}

void game::GameScene::renderGUI(engine::Window *window) {
}

void game::GameScene::initKeyboardEvents() {

	gameKeyboard.W.onPress.connect([this] {
		player->moveForward(gameKeyboard.getDeltaTimeOfState());
	});

	gameKeyboard.S.onPress.connect([this] {

		player->moveBackward(gameKeyboard.getDeltaTimeOfState());
	});

	gameKeyboard.D.onPress.connect([this] {

		player->moveRight(gameKeyboard.getDeltaTimeOfState());
	});

	gameKeyboard.A.onPress.connect([this] {

		player->moveLeft(gameKeyboard.getDeltaTimeOfState());
	});

	gameKeyboard.Space.onPress.connect([this] {

		auto time = gameKeyboard.getDeltaTimeOfState();
		player->moveUp(gameKeyboard.isShiftPressed() ? -time : time);
	});
}
void game::GameScene::initMouseEvents() {
	mouse.onMove.connect([this](double dx, double dy) {

		player->rotateLeft(dx);
		player->rotateUp(dy);

	});
}
