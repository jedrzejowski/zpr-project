#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace game {
	class MainGame : public Object {
	private:
		GameScene *gameScene = nullptr;
		engine::InputInterfacePtr inputInterface;
		map::WorldPtr worldMap;
		map::WorldRendererPtr mapRenderer = nullptr;
		PlayerPtr player;

		void initInputInterface();

	public:

		explicit MainGame(GameScene *scene);

		void renderWorld();
		void renderPlayerInterface();

		const Signal<> onMenuRequest;

		engine::InputInterfacePtr getInputInterface();

		void pollEvents();
	};
}
