/**
 * @file WelcomeScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/gui/GUI.h"

namespace menu {

	/**
	 * @brief Scena powitalna
	 */
	class WelcomeScene : public engine::Scene, public VirtualSharePtrObject<WelcomeScene> {
	public:
		using VirtualSharePtrObject<WelcomeScene>::shared_from_this;
	private:
		gui::InterfacePtr interface;
		gui::ButtonPtr play_button, settings_button, quit_button;

		explicit WelcomeScene();
		void constructorWelcomeScene();
	public:
		static WelcomeScenePtr create();
		~WelcomeScene();
		void render(engine::WindowPtr &window) override;
	};
}


