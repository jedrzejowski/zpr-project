#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"

namespace game {
	class GameScene : public engine::Scene {
	protected:
		map::WorldMap *worldMap;
		map::Renderer *mapRenderer;
		Player* player;
	public:
		GameScene();
		void render3D(engine::Window *window) override;
		void renderGUI(engine::Window *window) override;
	};
}