/**
 * @file InGameMenu.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {

	/**
	 * @brief Menu w trakcie gry
	 */
	class InGameMenu : public gui::Interface, public VirtualSharePtrObject<InGameMenu> {
	public:
		using VirtualSharePtrObject<InGameMenu>::shared_from_this;
		using VirtualSharePtrObject<InGameMenu>::weak_from_this;
	private:

		gui::ButtonPtr resume_button_ptr, save_btn_ptr;

		explicit InGameMenu(GameScenePtr &scene);
		void constructorInGameMenu();
	public:
		static InGameMenuPtr create(GameScenePtr &scene);

		const Signal<> onMenuExit;
		const Signal<> onSaveAndExit;
	};
}
