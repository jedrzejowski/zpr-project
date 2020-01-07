#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface, public virtual_enable_shared_from_this<InGameMenu> {
	private:

		gui::ButtonPtr resumeBtn, saveBtn;

		explicit InGameMenu(GameScenePtr& scene);
		void initEvents();
	public:
		static InGameMenuPtr create(GameScenePtr& scene);

		const Signal<> onMenuExit;
		const Signal<> onSaveAndExit;
	};
}
