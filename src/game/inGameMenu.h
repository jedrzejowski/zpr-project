#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface {
	private:
		GameScene *gameScene;
		engine::InputInterface *inputInterface;
		gui::Button *button;

		void initInputInterface();

	public:
		explicit InGameMenu(GameScene *scene);

		engine::InputInterface *getInputInterface() const;

		const Signal<> onMenuExit;
	};
}
