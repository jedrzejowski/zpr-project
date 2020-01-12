/**
 * @file WorldsScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

namespace menu {
	class WorldsScene : public engine::Scene, public VirtualSharePtrObject<WorldsScene> {
	public:
		using VirtualSharePtrObject<WorldsScene>::shared_from_this;
		using VirtualSharePtrObject<WorldsScene>::weak_from_this;
	private:
		gui::InterfacePtr interface;
		std::vector<gui::TriButtonPtr> worlds_button;
		gui::ButtonPtr add_button, return_button;
		float scroll_offset = 0;

		explicit WorldsScene();
		void constructorWorldsScene();

		void newWorldButton(const std::string &code_name);

		void backToWelcomeScene();
		void updateButtonsPositions();
		void initNewWorld();
	public:
		static WorldsScenePtr create();
		~WorldsScene() override;

		void render(engine::WindowPtr &window) override;
		void pollEvents() override;
	};
}