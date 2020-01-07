/**
 * @file InGameMenu.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public gui::Interface, public VirtualSharePtrObject<InGameMenu> {
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
