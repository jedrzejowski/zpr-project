#pragma once

#include "src/gengine/gEngine.h"
#include "src/map/Map.h"

class GameScene : public gengine::Scene {
protected:
	map::WorldMap *worldMap;
	map::Chunk* chunk;
	gengine::Shader *shader;
public:
	GameScene();
	void render3D(gengine::Window *window) override;
	void renderGUI(gengine::Window *window) override;
};

