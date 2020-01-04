#include "gameScene.h"
#include "player.h"
#include "inGameMenu.h"
#include "mainGame.h"
#include "src/menu/welcome.h"

game::GameScene::GameScene() {

	mainGame = std::make_shared<MainGame>(this->shared_from_this());
	inGameMenu = std::make_shared<InGameMenu>(this->shared_from_this());

	setInterfaceState(Game);

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
		winPtr->setScene(std::make_shared<menu::WelcomeScene>());
	});
}

void game::GameScene::render(engine::WindowPtr window) {

	mainGame->renderWorld();

	// Renderowanie interfejsu użytkownika
	glClear(GL_DEPTH_BUFFER_BIT); // Musimy wyczyścić sprawdzanie głębi ponieważ rysujemy interfejs

	auto me = shared_from_this();

	if (interfaceState == Game)
		mainGame->renderPlayerInterface();
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
