#pragma once

#include "src/_classdef.h"
#include "src/gui/GUI.h"

namespace game {
	class PlayerInterface : public gui::Interface, public virtual_enable_shared_from_this<PlayerInterface> {
	private:
		explicit PlayerInterface(game::GameScenePtr &scene);

		std::vector<gui::RectangleObjPtr> items;
		int selected = 0;

		void addItem(int texX, int texY);

	public:
		static PlayerInterfacePtr create(game::GameScenePtr &scene);
		~PlayerInterface() override;
	};
}
