//
// Created by adam on 16.10.2019.
//

#include "gamescene.h"

GameScene::GameScene() {
	worldMap = new map::WorldMap();
	worldMap->setChunk(0, 0, new map::Chunk());
	mapRenderer = new map::Renderer(worldMap);
}

void GameScene::render3D(gengine::Window *window) {
	mapRenderer->render();
}

void GameScene::renderGUI(gengine::Window *window) {
}