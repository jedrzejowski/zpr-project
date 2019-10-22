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

	logger.warn("inicljowanie");
	keyboard.W.onPressed.connect([]() {
		logger.warn("W pressed");
	});

	keyboard.W.onPress.connect([]() {
		logger.warn("W press");
	});
}
