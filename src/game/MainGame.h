/**
 * @file MainGame.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "src/engine/Engine.h"

namespace game {

	/**
	 * @brief Główny obiekt gry
	 */
	class MainGame : public Object {
	private:
		GameSceneWPtr game_scene;
		engine::InputInterfacePtr input_interface;
		map::WorldPtr world_map_ptr;
		map::WorldRendererPtr map_renderer_ptr;
		PlayerPtr player_ptr;
		PlayerInterfacePtr player_interface_ptr;

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
