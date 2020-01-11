/**
 * @file SettingsScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/gui/Interface.h"

namespace menu {

	class SettingsScene : public engine::Scene {
	private:
		gui::InterfacePtr interface;
		gui::TriButtonPtr camera_angle_button;
		gui::TriButtonPtr chunk_render_button;

		explicit SettingsScene();
		void constructorSettingsScene();
	public:
		static SettingsScenePtr create();
		~SettingsScene() override;
		void render(engine::WindowPtr& window) override;
	};
}