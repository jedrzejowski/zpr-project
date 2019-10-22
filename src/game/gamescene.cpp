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

	mapRenderer = new map::Renderer(player, worldMap);
	mapRenderer->setParent(this);

	onWindowChanged.connect([this]() {
		initKeyboardEvents();
	});
}

void game::GameScene::render3D(engine::Window *window) {
	mapRenderer->render(this);
}

void game::GameScene::renderGUI(engine::Window *window) {
}

void game::GameScene::initKeyboardEvents() {
	auto &keyboard = getWindow()->getKeyboard();

	keyboard.W.onPress.connect([this, &keyboard]() {

		player->moveForward(keyboard.getDeltaTimeOfState());
	});

	keyboard.S.onPress.connect([this, &keyboard]() {

		player->moveBackward(keyboard.getDeltaTimeOfState());
	});

	keyboard.D.onPress.connect([this, &keyboard]() {

		player->moveRight(keyboard.getDeltaTimeOfState());
	});

	keyboard.A.onPress.connect([this, &keyboard]() {

		player->moveLeft(keyboard.getDeltaTimeOfState());
	});

	keyboard.Space.onPress.connect([this, &keyboard]() {

		auto time = keyboard.getDeltaTimeOfState();
		player->moveUp(keyboard.isShiftPressed() ? -time : time);
	});
}
