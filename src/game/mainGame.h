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
		map::WorldRendererPtr mapRenderer;
		PlayerPtr player;
		PlayerInterfacePtr playerInterface;


		SelectedBlockPtr selectedBlock;

		void initInputInterface();

		explicit MainGame(GameScenePtr& scene);
	public:
		static MainGamePtr create(GameScenePtr& scene);

		void renderWorld();

		const Signal<> onMenuRequest;

		engine::InputInterfacePtr getInputInterface();

		void pollEvents();

		const GameSceneWPtr &getGameScene() const;
		const map::WorldPtr &getWorldMap() const;
		const map::WorldRendererPtr &getMapRenderer() const;
		const PlayerPtr &getPlayer() const;
		const SelectedBlockPtr &getSelectedBlock() const;
		const PlayerInterfacePtr &getPlayerInterface() const;
	};
}
