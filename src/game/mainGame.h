#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"

namespace game {
	class MainGame : public Object {
	private:
		GameScene *gameScene = nullptr;
		engine::InputInterface *inputInterface = nullptr;
		map::WorldPtr worldMap;
		map::WorldRendererPtr mapRenderer = nullptr;
		PlayerPtr player;

		void initInputInterface();

	public:

		explicit MainGame(GameScene *scene);

		void renderWorld();
		void renderPlayerInterface();

		const Signal<> onMenuRequest;

		engine::InputInterface *getInputInterface() const;

		void pollEvents();
	};
}
