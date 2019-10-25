#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "src/lib/object.h"
#include "inGameMenu.h"

namespace game {
	enum GameSceneState {
		Game,
		Menu
	};

	class GameScene : public engine::Scene {
	private:
		GameSceneState interfaceState;

		engine::InputInterface gameInput;
		InGameMenu *inGameMenu;

		map::WorldMap *worldMap;
		map::Renderer *mapRenderer;
		Player *player;

		void initGameEvents();
		void initMenuEvents();
	public:
		GameScene();
		void render3D(engine::Window *window) override;
		void renderGUI(engine::Window *window) override;

		GameSceneState getInterfaceState() const;
		void setInterfaceState(GameSceneState interfaceState);
	};
}