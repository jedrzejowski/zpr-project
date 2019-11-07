//
// Created by adam on 07.11.2019.
//

#include "mainMenu.h"

menu::MainMenu::MainMenu() {
}

void menu::MainMenu::render(engine::Window *window) {

}

menu::MainMenuState menu::MainMenu::getState() const {
	return state;
}

void menu::MainMenu::setState(menu::MainMenuState newState) {
	auto oldState = state;
	state = oldState;

	onStateChanged(oldState, newState);
}
