#include "gameScene.h"
#include "player.h"
#include "inGameMenu.h"
#include "mainGame.h"
#include "playerInterface.h"
#include "src/menu/welcome.h"

game::GameScene::GameScene() {
	logger.constructor(this);
}
game::GameScene::~GameScene() {
	logger.destructor(this);
}


game::GameScenePtr game::GameScene::create() {
	struct trick : GameScene {
	};

	GameScenePtr self = std::make_shared<trick>();

	self->mainGame = MainGame::create(self);
	self->inGameMenu = InGameMenu::create(self);
	self->playerInterface = PlayerInterface::create(self);

	self->setInterfaceState(Game);

	self->initEvents();

	return self;
}

void game::GameScene::initEvents() {
	mainGame->onMenuRequest([&]() {
		setInterfaceState(Menu);
	});

	inGameMenu->onMenuExit([&]() {
		setInterfaceState(Game);
	});

	inGameMenu->onSaveAndExit([&] {
		auto winWPtr = getWindow();
		if (winWPtr.expired()) return;
		auto winPtr = winWPtr.lock();
		winPtr->setScene(menu::WelcomeScene::create());
	});
}


void game::GameScene::render(engine::WindowPtr window) {

	mainGame->renderWorld();

	// Renderowanie interfejsu użytkownika
	glClear(GL_DEPTH_BUFFER_BIT); // Musimy wyczyścić sprawdzanie głębi ponieważ rysujemy interfejs

	auto me = shared_from_this();

	if (interfaceState == Game)
		playerInterface->render(me);
	if (interfaceState == Menu)
		inGameMenu->render(me);
}


game::GameSceneState game::GameScene::getInterfaceState() const {
	return interfaceState;
}

void game::GameScene::setInterfaceState(game::GameSceneState interfaceState) {
	this->interfaceState = interfaceState;


	switch (interfaceState) {
		case Game:
			setInputInterface(mainGame->getInputInterface());
			break;
		case Menu:
			setInputInterface(inGameMenu->getInputInterface());
			break;
	}
}

void game::GameScene::pollEvents() {
	mainGame->pollEvents();
}