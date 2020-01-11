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

		gui::ButtonPtr resume_button_ptr, save_btn_ptr;

		explicit InGameMenu(GameScenePtr& scene);
		void constructorInGameMenu();
	public:
		static InGameMenuPtr create(GameScenePtr& scene);

		const Signal<> onMenuExit;
		const Signal<> onSaveAndExit;
	};
}
