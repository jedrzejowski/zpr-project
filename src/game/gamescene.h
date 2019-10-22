#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "src/lib/object.h"

namespace game {
	class GameScene : public engine::Scene {
	private:

		engine::Keyboard gameKeyboard;
		engine::Keyboard guiKeyboard;

		map::WorldMap *worldMap;
		map::Renderer *mapRenderer;
		Player* player;

		void initKeyboardEvents();
		void initMouseEvents();
	public:
		GameScene();
		void render3D(engine::Window *window) override;
		void renderGUI(engine::Window *window) override;


	};
}