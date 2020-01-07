#pragma once

#include <src/block/Wall.h>
#include "_classdef.h"
#include "src/engine/Engine.h"
#include "src/block/FullPosition.h"
#include "src/lib/Object.hpp"

namespace game {
	class SelectedBlock : public Object {
	private:
		block::FullPosition pointingPos;
		block::FullPosition newBlockPos;
		bool selected;

		MainGameWPtr mainGame;

	public:
		explicit SelectedBlock(MainGamePtr &mainGame);
		~SelectedBlock() override;

		const block::FullPosition &getPointingPos() const;
		const block::FullPosition &getNewBlockPos() const;
		bool isSelected() const;

		void update();
	};
}
