#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

namespace game {
	class MainGame : public Object {
	private:
		GameScene *gameScene;
		engine::InputInterface *inputInterface;
		map::WorldMap *worldMap;
		map::Renderer *mapRenderer;
		Player *player;

		void initInputInterface();

	public:

		explicit MainGame(GameScene *scene);

		void renderWorld();
		void renderPlayerInterface();

		const Signal<> onMenuRequest;

		engine::InputInterface *getInputInterface() const;
	};
}
