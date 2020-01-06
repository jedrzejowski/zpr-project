#include "mainGame.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "player.h"
#include "gameScene.h"
#include "playerInterface.h"
#include "selectedBlock.h"

game::MainGame::MainGame(GameScenePtr &scene) {
	gameScene = scene;
}


game::MainGamePtr game::MainGame::create(game::GameScenePtr &scene) {
	struct trick : MainGame {
		trick(GameScenePtr &scene) : MainGame(scene) {}
	};

	game::MainGamePtr self = std::make_shared<trick>(scene);

	self->worldMap = std::make_shared<map::World>("default");

	self->player = std::make_shared<Player>();

	self->mapRenderer = map::WorldRenderer::create(self->worldMap);

	self->selectedBlock = std::make_shared<game::SelectedBlock>(self);

	self->initInputInterface();

	return self;
}


void game::MainGame::renderWorld() {
	mapRenderer->render(
			player->getCamera(),
			gameScene.lock()
	);
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

	mouse->onLeave([&] {
		onMenuRequest();
	});

	mouse->Left.onPressed([&] {
		if (!selectedBlock->isSelected()) return;

		auto fullPos = selectedBlock->getPointingPos();

		if (auto chunk = worldMap->getChunk(fullPos.getChunk()).lock()) {

			chunk->setAir(fullPos.getBlock());
		}
	});

	mouse->Right.onPressed([&] {
	});

	keyboard->Num1.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(0);
	});

	keyboard->Num2.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(1);
	});

	keyboard->Num3.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(2);
	});

	keyboard->Num4.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(3);
	});

	keyboard->Num5.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(4);
	});

	keyboard->Num6.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(5);
	});

	keyboard->Num7.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(6);
	});

	keyboard->Num8.onPressed([this] {
		if (gameScene.expired()) return;
		gameScene.lock()->getPlayerInterface()->setItem(7);
	});
}

engine::InputInterfacePtr game::MainGame::getInputInterface() {
	return inputInterface;
}

void game::MainGame::pollEvents() {
	worldMap->syncChunkWithLoader();
	worldMap->loadForPlayer(player);
	selectedBlock->update();
}

const game::GameSceneWPtr &game::MainGame::getGameScene() const {
	return gameScene;
}

const map::WorldPtr &game::MainGame::getWorldMap() const {
	return worldMap;
}

const map::WorldRendererPtr &game::MainGame::getMapRenderer() const {
	return mapRenderer;
}

const game::PlayerPtr &game::MainGame::getPlayer() const {
	return player;
}

const game::SelectedBlockPtr &game::MainGame::getSelectedBlock() const {
	return selectedBlock;
}
