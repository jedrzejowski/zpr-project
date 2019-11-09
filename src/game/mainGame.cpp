#include "mainGame.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "player.h"
#include "gameScene.h"

game::MainGame::MainGame(GameScene *scene) :
		Object(scene) {
	gameScene = scene;

	worldMap = new map::World();

	player = new Player(worldMap);
	player->setParent(this);

	mapRenderer = new map::WorldRenderer(worldMap);
	mapRenderer->setParent(this);

	initInputInterface();
}


void game::MainGame::renderWorld() {
	mapRenderer->render(
			player->getCamera(),
			gameScene
	);
}

void game::MainGame::renderPlayerInterface() {
}

void game::MainGame::initInputInterface() {
	inputInterface = new engine::InputInterface(this);

	auto keyboard = inputInterface->getKeyboard();
	auto mouse = inputInterface->getMouse();

	mouse->setAttachedToCenter(true);

	keyboard->W.onPress([this, keyboard] {
		player->moveForward(keyboard->getDeltaTimeOfState());
	});

	keyboard->S.onPress([this, keyboard] {
		player->moveBackward(keyboard->getDeltaTimeOfState());
	});

	keyboard->D.onPress([this, keyboard] {
		player->moveRight(keyboard->getDeltaTimeOfState());
	});

	keyboard->A.onPress([this, keyboard] {
		player->moveLeft(keyboard->getDeltaTimeOfState());
	});

	keyboard->Space.onPress([this, keyboard] {
		player->moveUp(keyboard->getDeltaTimeOfState());
	});

	keyboard->LShift.onPress([this, keyboard] {
		player->moveDown(keyboard->getDeltaTimeOfState());
	});

	keyboard->Escape.onPressed([this, keyboard] {
		onMenuRequest();
	});

	mouse->onMove([&](const glm::vec2& delta) {
		player->rotateRight(delta.x);
		player->rotateDown(delta.y);
	});

	mouse->onLeave([&]() {
		onMenuRequest();
	});
}

engine::InputInterface *game::MainGame::getInputInterface() const {
	return inputInterface;
}

void game::MainGame::pollEvents() {
	worldMap->syncChunkWithLoader();
	player->requestChunks();
}

