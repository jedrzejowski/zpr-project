#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/gui/GUI.h"

namespace menu {

	class WelcomeScene : public engine::Scene, virtual_enable_shared_from_this<WelcomeScene> {
		using virtual_enable_shared_from_this<WelcomeScene>::shared_from_this;
	private:
		gui::InterfacePtr interface;
		gui::ButtonPtr worldsBtn, settingsBtn, quitBtn;

	public:
		explicit WelcomeScene();
		~WelcomeScene();
		void render(engine::WindowPtr window) override;
	};
}


