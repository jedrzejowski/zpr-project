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

		MainGame* mainGame = nullptr;
		InGameMenu *inGameMenu = nullptr;

	public:
		GameScene();
		void render(engine::Window *window) override;

		GameSceneState getInterfaceState() const;
		void setInterfaceState(GameSceneState interfaceState);
	};
}