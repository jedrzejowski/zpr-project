#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "src/lib/object.h"
#include "inGameMenu.h"

namespace game {
	class GameScene : public engine::Scene {
	private:

		engine::InputInterface gameInput;
		engine::InputInterface menuInput;
		InGameMenu* inGameMenu;

		map::WorldMap *worldMap;
		map::Renderer *mapRenderer;
		Player* player;

		void initGameEvents();
		void initMenuEvents();
	public:
		GameScene();
		void render3D(engine::Window *window) override;
		void renderGUI(engine::Window *window) override;


	};
}