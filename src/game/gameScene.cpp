#include "gameScene.h"
#include "player.h"
#include "inGameMenu.h"
#include "mainGame.h"
#include "src/menu/welcome.h"

game::GameScene::GameScene() {

	mainGame = new MainGame(this);
	inGameMenu = new InGameMenu(this);

	setInterfaceState(Game);

	mainGame->onMenuRequest([&]() {
		setInterfaceState(Menu);
	});

	inGameMenu->onMenuExit([&]() {
		setInterfaceState(Game);
	});

	inGameMenu->onSaveAndExit([&]{
		getWindow()->setScene(new menu::WelcomeScene);
	});
}

void game::GameScene::render(engine::Window *window) {

	mainGame->renderWorld();

	// Renderowanie interfejsu użytkownika
	glClear(GL_DEPTH_BUFFER_BIT); // Musimy wyczyścić sprawdzanie głębi ponieważ rysujemy interfejs

	if (interfaceState == Game)
		mainGame->renderPlayerInterface();
	if (interfaceState == Menu) {
		inGameMenu->render(this);
	}
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
