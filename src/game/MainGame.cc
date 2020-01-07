/**
 * @file MainGame.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "MainGame.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "Player.h"
#include "GameScene.h"
#include "PlayerInterface.h"
#include "SelectedBlock.h"

game::MainGame::MainGame(GameScenePtr &scene) {
	gameScene = scene;
}


game::MainGamePtr game::MainGame::create(game::GameScenePtr &scene) {
	struct trick : MainGame {
		trick(GameScenePtr &scene) : MainGame(scene) {}
	};

	game::MainGamePtr self = std::make_shared<trick>(scene);

	self->worldMap = map::World::create("default");

	self->player = std::make_shared<Player>();

	self->playerInterface = PlayerInterface::create(self);

	self->mapRenderer = map::WorldRenderer::create(self->worldMap);

	self->selectedBlock = std::make_shared<game::SelectedBlock>(self);

	self->initInputInterface();

	return self;
}


void game::MainGame::renderWorld() {
	auto scene = gameScene.lock();

	mapRenderer->render(
			player->getCamera(),
			scene
	);

	if (scene->getInterfaceState() == Game)
		playerInterface->render(scene);
}

void game::MainGame::initInputInterface() {
	inputInterface = std::make_shared<engine::InputInterface>();

	auto keyboard = inputInterface->getKeyboard();
	auto mouse = inputInterface->getMouse();

	mouse->setAttachedToCenter(true);

	keyboard->W.onPress([this] {
		player->moveForward(inputInterface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->S.onPress([this] {
		player->moveBackward(inputInterface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->D.onPress([this] {
		player->moveRight(inputInterface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->A.onPress([this] {
		player->moveLeft(inputInterface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->Space.onPress([this] {
		player->moveUp(inputInterface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->LShift.onPress([this] {
		player->moveDown(inputInterface->getKeyboard()->getDeltaTimeOfState());
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

		if (auto chunk = worldMap->getChunk(fullPos.getChunk()).lock())
			chunk->setAir(fullPos.getBlock());
	});

	mouse->Right.onPressed([&] {
		playerInterface->useItem();
	});

	keyboard->Num1.onPressed([this] {
		playerInterface->selectItem(0);
	});

	keyboard->Num2.onPressed([this] {
		playerInterface->selectItem(1);
	});

	keyboard->Num3.onPressed([this] {
		playerInterface->selectItem(2);
	});

	keyboard->Num4.onPressed([this] {
		playerInterface->selectItem(3);
	});

	keyboard->Num5.onPressed([this] {
		playerInterface->selectItem(4);
	});

	keyboard->Num6.onPressed([this] {
		playerInterface->selectItem(5);
	});

	keyboard->Num7.onPressed([this] {
		playerInterface->selectItem(6);
	});

	keyboard->Num8.onPressed([this] {
		playerInterface->selectItem(7);
	});

	keyboard->Num9.onPressed([this] {
//		playerInterface->selectItem(8);
	});

	keyboard->Num0.onPressed([this] {
//		playerInterface->selectItem(9);
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

const game::PlayerInterfacePtr &game::MainGame::getPlayerInterface() const {
	return playerInterface;
}
