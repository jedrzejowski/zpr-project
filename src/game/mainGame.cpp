#include "mainGame.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "player.h"
#include "gameScene.h"

game::MainGame::MainGame(GameScenePtr &scene) {
	gameScene = scene;
}


game::MainGamePtr game::MainGame::create(game::GameScenePtr &scene) {
	struct trick : MainGame {
		trick(GameScenePtr &scene) : MainGame(scene) {}
	};

	auto self = std::make_shared<trick>(scene);

	self->worldMap = std::make_shared<map::World>("default");

	self->player = std::make_shared<Player>();

	self->mapRenderer = std::make_shared<map::WorldRenderer>(self->worldMap);

	self->initInputInterface();

	return self;
}


void game::MainGame::renderWorld() {
	mapRenderer->render(
			player->getCamera(),
			gameScene.lock()
	);
}

void game::MainGame::renderPlayerInterface() {
}

void game::MainGame::initInputInterface() {
	inputInterface = std::make_shared<engine::InputInterface>();

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

	mouse->onMove([&](const glm::vec2 &delta) {
		player->rotateRight(delta.x);
		player->rotateDown(delta.y);
	});

	mouse->onLeave([&]() {
		onMenuRequest();
	});
}

engine::InputInterfacePtr game::MainGame::getInputInterface() {
	return inputInterface;
}

void game::MainGame::pollEvents() {
	worldMap->syncChunkWithLoader();
	mapRenderer->syncWithWorld();
	worldMap->loadForPlayer(player);
}