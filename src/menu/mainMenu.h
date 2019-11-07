#pragma once

#include "src/engine/Engine.h"

namespace menu {
	enum MainMenuState {
		Welcome,
		Settings,
		Worlds
	};

	class MainMenu : public engine::Scene {
	private:
		MainMenuState state;
	public:
		explicit MainMenu();
		void render(engine::Window *window) override;

		MainMenuState getState() const;
		void setState(MainMenuState state);

		const Signal<MainMenuState, MainMenuState> onStateChanged;
	};
}

