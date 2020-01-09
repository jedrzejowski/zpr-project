/**
 * @file PlayerInterface.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class PlayerInterface : public gui::Interface, public VirtualSharePtrObject<PlayerInterface> {
	private:
		game::MainGameWPtr sceneWPtr;
		explicit PlayerInterface(game::MainGamePtr &scene);

		const int item_limit;

		std::vector<PlayerItemPtr> items;
		gui::RectangleObjPtr background;
		int selected_slot_index = 0;

		void updateItemModel(int index);

		void assertIndexValid(int index);

	public:
		static PlayerInterfacePtr create(MainGamePtr &scene);
		~PlayerInterface() override;

		void setSlot(int index, PlayerItemPtr &item);
		void selectSlot(int index);
		bool isItemSlotEmpty(int index);

		void useItem();
	};
}
