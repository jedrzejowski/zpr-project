/**
 * @file GameScene.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "GameScene.h"
#include "Player.h"
#include "InGameMenu.h"
#include "MainGame.h"
#include "PlayerInterface.h"
#include "src/menu/WelcomeScene.h"

game::GameScene::GameScene() {
	logger(4).constructor(this);
}
game::GameScene::~GameScene() {
	logger(4).destructor(this);
}


game::GameScenePtr game::GameScene::create() {
	struct Self : GameScene {
	};

	GameScenePtr self = std::make_shared<Self>();

	self->main_game = MainGame::create(self);
	self->in_game_menu = InGameMenu::create(self);

	self->setInterfaceState(Game);

	self->initEvents();

	return self;
}

void game::GameScene::initEvents() {
	main_game->onMenuRequest([&]() {
		setInterfaceState(Menu);
	});

	in_game_menu->onMenuExit([&]() {
		setInterfaceState(Game);
	});

	in_game_menu->onSaveAndExit([&] {
		auto winWPtr = getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();
		winPtr->setScene(menu::WelcomeScene::create());
	});
}


void game::GameScene::render(engine::WindowPtr& window) {

	main_game->renderWorld();

	// Renderowanie interfejsu użytkownika
	glClear(GL_DEPTH_BUFFER_BIT); // Musimy wyczyścić sprawdzanie głębi ponieważ rysujemy interfejs

	auto me = shared_from_this();

	if (interface_state == Menu)
		in_game_menu->render(me);
}


game::GameSceneState game::GameScene::getInterfaceState() const {
	return interface_state;
}

void game::GameScene::setInterfaceState(game::GameSceneState interfaceState) {
	this->interface_state = interfaceState;


	switch (interfaceState) {
		case Game:
			setInputInterface(main_game->getInputInterface());
			break;
		case Menu:
			setInputInterface(in_game_menu->getInputInterface());
			break;
	}
}

void game::GameScene::pollEvents() {
	main_game->pollEvents();
}

const game::MainGamePtr &game::GameScene::getMainGame() const {
	return main_game;
}

const game::InGameMenuPtr &game::GameScene::getInGameMenu() const {
	return in_game_menu;
}
