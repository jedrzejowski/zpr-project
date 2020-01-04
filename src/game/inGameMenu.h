#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface, virtual_enable_shared_from_this<InGameMenu> {
	private:

		gui::ButtonPtr resumeBtn, saveBtn;

	public:
		explicit InGameMenu(GameSceneWPtr scene);

		const Signal<> onMenuExit;
		const Signal<> onSaveAndExit;
	};
}
