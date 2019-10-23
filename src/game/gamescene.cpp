//
// Created by adam on 16.10.2019.
//

#include <src/logger.h>
#include "gamescene.h"
#include "player.h"

game::GameScene::GameScene() {
	worldMap = new map::WorldMap();

	auto chunk = new map::Chunk(coord2D(0, 0));
	worldMap->setChunk(chunk);

	player = new Player();
	player->setParent(this);

	mapRenderer = new map::Renderer(this, player, worldMap);
	mapRenderer->setParent(this);

	initGameEvents();

	setInputInterface(&gameInput);
}

void game::GameScene::render3D(engine::Window *window) {
	mapRenderer->render(this);
}

void game::GameScene::renderGUI(engine::Window *window) {
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
		auto time = keyboard.getDeltaTimeOfState();
		player->moveUp(keyboard.isShiftPressed() ? -time : time);
	});

	mouse.onMove.connect([&](double dx, double dy) {
		player->rotateLeft(dx);
		player->rotateUp(dy);
	});
}
