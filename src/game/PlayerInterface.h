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
		explicit PlayerInterface(game::MainGamePtr &scene);

		int itemLimit;

		std::vector<PlayerItemPtr> items;
		gui::RectangleObjPtr background;
		int selected = 0;

		void updateItemModel(int index);

	public:
		static PlayerInterfacePtr create(MainGamePtr &scene);
		~PlayerInterface() override;

		void selectItem(int index);
		void setItem(int index, PlayerItemPtr &item);

		void useItem();
	};
}
