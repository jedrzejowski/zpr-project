/**
 * @file MainGame.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "src/engine/Engine.h"

namespace game {
	class MainGame : public Object {
	private:
		GameSceneWPtr gameScene;
		engine::InputInterfacePtr input_interface;
		map::WorldPtr worldMap;
		map::WorldRendererPtr mapRenderer;
		PlayerPtr player;
		PlayerInterfacePtr player_interface;

		void initInputInterface();

		explicit MainGame(GameScenePtr& scene);
	public:
		static MainGamePtr create(GameScenePtr& scene);
		virtual ~MainGame();

		void renderWorld();

		const Signal<> onMenuRequest;

		engine::InputInterfacePtr getInputInterface();

		void pollEvents();

		const GameSceneWPtr &getGameScene() const;
		const map::WorldPtr &getWorldMap() const;
		const map::WorldRendererPtr &getMapRenderer() const;
		const PlayerPtr &getPlayer() const;
		const PlayerInterfacePtr &getPlayerInterface() const;
	};
}
