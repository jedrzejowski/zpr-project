#include "mainGame.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "player.h"
#include "gameScene.h"

game::MainGame::MainGame(GameScene *scene) :
		Object(scene) {
	gameScene = scene;

	worldMap = new map::WorldMap();

	player = new Player();
	player->setParent(this);

	mapRenderer = new map::Renderer(worldMap);
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

	auto &keyboard = inputInterface->getKeyboard();
	auto &mouse = inputInterface->getMouse();

	mouse.setAttachedToCenter(true);

	keyboard.W.onPress([&] {
		player->moveForward(keyboard.getDeltaTimeOfState());
	});

	keyboard.S.onPress([&] {
		player->moveBackward(keyboard.getDeltaTimeOfState());
	});

	keyboard.D.onPress([&] {
		player->moveRight(keyboard.getDeltaTimeOfState());
	});

	keyboard.A.onPress([&] {
		player->moveLeft(keyboard.getDeltaTimeOfState());
	});

	keyboard.Space.onPress([&] {
		player->moveUp(keyboard.getDeltaTimeOfState());
	});

	keyboard.LShift.onPress([&] {
		player->moveDown(keyboard.getDeltaTimeOfState());
	});

	keyboard.Escape.onPressed([&] {
		onMenuRequest();
	});

	mouse.onMove([&](double dx, double dy) {
		player->rotateRight(dx);
		player->rotateDown(dy);
	});

	mouse.onLeave([&]() {
		onMenuRequest();
	});
}

engine::InputInterface *game::MainGame::getInputInterface() const {
	return inputInterface;
}

