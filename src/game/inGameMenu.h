#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface {
	private:
		GameScene *scene;
		gui::Button *button;

	public:
		explicit InGameMenu(GameScene *scene);

	};
}
