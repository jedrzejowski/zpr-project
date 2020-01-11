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
	game_scene = scene;
}


game::MainGamePtr game::MainGame::create(game::GameScenePtr &scene) {
	struct trick : MainGame {
		trick(GameScenePtr &scene) : MainGame(scene) {}
	};

	game::MainGamePtr self = std::make_shared<trick>(scene);

	self->world_map_ptr = map::World::create("default");
	self->player_ptr = Player::create(self->world_map_ptr);

	self->map_renderer_ptr = map::WorldRenderer::create(self->world_map_ptr);
	self->player_interface_ptr = PlayerInterface::create(self);

	self->initInputInterface();

	return self;
}

game::MainGame::~MainGame() {

	player_ptr->saveObjectToFile();
	world_map_ptr->fullSave();
}


void game::MainGame::renderWorld() {
	auto scene = game_scene.lock();

	map_renderer_ptr->render(player_ptr->getCamera(), scene);

	if (scene->getInterfaceState() == Game)
		player_interface_ptr->render(scene);
}

void game::MainGame::initInputInterface() {
	input_interface = std::make_shared<engine::InputInterface>();

	auto keyboard = input_interface->getKeyboard();
	auto mouse = input_interface->getMouse();

	mouse->setAttachedToCenter(true);

	keyboard->W.onPress([this] {
		player_ptr->moveForward(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->S.onPress([this] {
		player_ptr->moveBackward(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->D.onPress([this] {
		player_ptr->moveRight(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->A.onPress([this] {
		player_ptr->moveLeft(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->Space.onPress([this] {
		player_ptr->moveUp(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->LShift.onPress([this] {
		player_ptr->moveDown(input_interface->getKeyboard()->getDeltaTimeOfState());
	});

	keyboard->Escape.onPressed([this, keyboard] {
		onMenuRequest();
	});

	mouse->onMove([&](const glm::vec2 &delta) {
		player_ptr->rotateRight(delta.x);
		player_ptr->rotateDown(delta.y);
	});

	mouse->onLeave([&] {
		onMenuRequest();
	});

	mouse->Left.onPressed([&] {
		if (!player_ptr->isPointingBlock()) return;

		auto fullPos = player_ptr->getPointingBlockPosition();

		if (auto chunk = world_map_ptr->getChunk(fullPos.getChunkCoord()).lock())
			chunk->setAir(fullPos.getBlockCoord());
	});

	mouse->Right.onPressed([&] {
		player_interface_ptr->useItem();
	});

	keyboard->Num1.onPressed([this] {
		player_interface_ptr->selectSlot(0);
	});

	keyboard->Num2.onPressed([this] {
		player_interface_ptr->selectSlot(1);
	});

	keyboard->Num3.onPressed([this] {
		player_interface_ptr->selectSlot(2);
	});

	keyboard->Num4.onPressed([this] {
		player_interface_ptr->selectSlot(3);
	});

	keyboard->Num5.onPressed([this] {
		player_interface_ptr->selectSlot(4);
	});

	keyboard->Num6.onPressed([this] {
		player_interface_ptr->selectSlot(5);
	});

	keyboard->Num7.onPressed([this] {
		player_interface_ptr->selectSlot(6);
	});

	keyboard->Num8.onPressed([this] {
		player_interface_ptr->selectSlot(7);
	});

	keyboard->Num9.onPressed([this] {
		player_interface_ptr->selectSlot(8);
	});

	keyboard->Num0.onPressed([this] {
		player_interface_ptr->selectSlot(9);
	});
}

engine::InputInterfacePtr game::MainGame::getInputInterface() {
	return input_interface;
}

void game::MainGame::pollEvents() {
	world_map_ptr->syncChunkWithLoader();
	world_map_ptr->loadForPlayer(player_ptr);
	player_ptr->resetBlockPointing();
}

const game::GameSceneWPtr &game::MainGame::getGameScene() const {
	return game_scene;
}

const map::WorldPtr &game::MainGame::getWorldMap() const {
	return world_map_ptr;
}

const map::WorldRendererPtr &game::MainGame::getMapRenderer() const {
	return map_renderer_ptr;
}

const game::PlayerPtr &game::MainGame::getPlayer() const {
	return player_ptr;
}

const game::PlayerInterfacePtr &game::MainGame::getPlayerInterface() const {
	return player_interface_ptr;
}