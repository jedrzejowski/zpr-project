#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class PlayerInterface : public gui::Interface, public virtual_enable_shared_from_this<PlayerInterface> {
	private:
		explicit PlayerInterface(game::MainGamePtr &scene);

		std::vector<gui::RectangleObjPtr> items;
		gui::RectangleObjPtr background;
		int selected = 0;

		void addItem(int texX, int texY);
		void setItemState(int index, bool selected);

	public:
		static PlayerInterfacePtr create(MainGamePtr &scene);
		~PlayerInterface() override;

		void selectItem(int index);

		void useItem();
	};
}
