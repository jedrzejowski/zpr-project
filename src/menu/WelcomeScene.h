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

	class WelcomeScene : public engine::Scene, public VirtualSharePtrObject<WelcomeScene> {
		using VirtualSharePtrObject<WelcomeScene>::shared_from_this;
	private:
		gui::InterfacePtr interface;
		gui::ButtonPtr playBtn, settingsBtn, quitBtn;

		explicit WelcomeScene();
		void initBtnActions();
	public:
		static WelcomeScenePtr create();
		~WelcomeScene();
		void render(engine::WindowPtr& window) override;
	};
}


