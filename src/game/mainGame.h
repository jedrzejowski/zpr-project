#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/engine/Engine.h"

namespace game {
	class MainGame : public Object {
	private:
		GameSceneWPtr gameScene;
		engine::InputInterfacePtr inputInterface;
		map::WorldPtr worldMap;
		map::WorldRendererPtr mapRenderer = nullptr;
		PlayerPtr player;

		void initInputInterface();

		explicit MainGame(GameScenePtr& scene);
	public:
		static MainGamePtr create(GameScenePtr& scene);

		void renderWorld();
		void renderPlayerInterface();

		const Signal<> onMenuRequest;

		engine::InputInterfacePtr getInputInterface();

		void pollEvents();
	};
}
