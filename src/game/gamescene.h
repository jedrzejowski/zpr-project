#pragma once

#include "src/gengine/gEngine.h"
#include "src/map/Map.h"

class GameScene : public engine::Scene {
protected:
	map::WorldMap *worldMap;
	map::Renderer* mapRenderer;
public:
	GameScene();
	void render3D(engine::Window *window) override;
	void renderGUI(engine::Window *window) override;
};

