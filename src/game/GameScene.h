/**
 * @file GameScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/map/Map.h"
#include "src/lib/Object.hpp"
#include "InGameMenu.h"

namespace game {
	enum GameSceneState {
		Game,
		Menu
	};

	class GameScene : public engine::Scene, public VirtualSharePtrObject<GameScene> {
	public:
		using VirtualSharePtrObject<GameScene>::shared_from_this;
		using VirtualSharePtrObject<GameScene>::weak_from_this;
	private:
		GameSceneState interface_state;

		MainGamePtr main_game;
		InGameMenuPtr in_game_menu;

		GameScene();
		void initEvents();
	public:
		~GameScene() override;
		static GameScenePtr create();
		void render(engine::WindowPtr& window) override;

		GameSceneState getInterfaceState() const;
		void setInterfaceState(GameSceneState interfaceState);

		const MainGamePtr &getMainGame() const;
		const InGameMenuPtr &getInGameMenu() const;

		void pollEvents() override;
	};
}