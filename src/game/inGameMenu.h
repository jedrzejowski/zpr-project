#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface {
	private:
		GameScene *gameScene = nullptr;

		gui::Button *resumeBtn = nullptr,
				*saveBtn = nullptr;

	public:
		explicit InGameMenu(GameScene *scene);

		const Signal<> onMenuExit;
		const Signal<> onSaveAndExit;
	};
}
