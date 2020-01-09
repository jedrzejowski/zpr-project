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

game::MainGame::MainGame(GameScenePtr &scene) {
	gameScene = scene;
}


game::MainGamePtr game::MainGame::create(game::GameScenePtr &scene) {
	struct trick : MainGame {
		trick(GameScenePtr &scene) : MainGame(scene) {}
	};

	game::MainGamePtr self = std::make_shared<trick>(scene);

	self->worldMap = map::World::create("default");

	self->player = Player::create(self);

	self->player_interface = PlayerInterface::create(self);

	self->mapRenderer = map::WorldRenderer::create(self->worldMap);

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
		player_interface->render(scene);
}

void game::MainGame::initInputInterface() {
	input_interface = std::make_shared<engine::InputInterface>();

	auto keyboard = input_interface->getKeyboard();
	auto mouse = input_interface->getMouse();

	mouse->setAttachedToCenter(true);

	keyboard->W.onPress([this] {
		player->moveForward(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->S.onPress([this] {
		player->moveBackward(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->D.onPress([this] {
		player->moveRight(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->A.onPress([this] {
		player->moveLeft(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->Space.onPress([this] {
		player->moveUp(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->LShift.onPress([this] {
		player->moveDown(input_interface->getKeyboard()->getDeltaTimeOfState());
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
		if (!player->isPointingBlock()) return;

		auto fullPos = player->getPointingBlockPosition();

		if (auto chunk = worldMap->getChunk(fullPos.getChunkCoord()).lock())
			chunk->setAir(fullPos.getBlockCoord());
	});

	mouse->Right.onPressed([&] {
		player_interface->useItem();
	});

	keyboard->Num1.onPressed([this] {
		player_interface->selectSlot(0);
	});

	keyboard->Num2.onPressed([this] {
		player_interface->selectSlot(1);
	});

	keyboard->Num3.onPressed([this] {
		player_interface->selectSlot(2);
	});

	keyboard->Num4.onPressed([this] {
		player_interface->selectSlot(3);
	});

	keyboard->Num5.onPressed([this] {
		player_interface->selectSlot(4);
	});

	keyboard->Num6.onPressed([this] {
		player_interface->selectSlot(5);
	});

	keyboard->Num7.onPressed([this] {
		player_interface->selectSlot(6);
	});

	keyboard->Num8.onPressed([this] {
		player_interface->selectSlot(7);
	});

	keyboard->Num9.onPressed([this] {
		player_interface->selectSlot(8);
	});

	keyboard->Num0.onPressed([this] {
		player_interface->selectSlot(9);
	});
}

engine::InputInterfacePtr game::MainGame::getInputInterface() {
	return input_interface;
}

void game::MainGame::pollEvents() {
	worldMap->syncChunkWithLoader();
	worldMap->loadForPlayer(player);
	player->resetBlockPointing();
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

const game::PlayerInterfacePtr &game::MainGame::getPlayerInterface() const {
	return player_interface;
}
