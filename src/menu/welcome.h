#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/gui/GUI.h"

namespace menu {

	class WelcomeScene : public engine::Scene {
	private:
		gui::InterfacePtr interface;
		gui::ButtonPtr worldsBtn, settingsBtn, quitBtn;

	public:
		explicit WelcomeScene();
		void render(engine::Window *window) override;
	};
}


