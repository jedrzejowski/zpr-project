#pragma once

#include "_classdef.h"
#include "src/engine/Engine.h"
#include "src/block/fullPosition.h"
#include "src/lib/object.h"

namespace game {
	class SelectedBlock : public Object {
	private:
		block::FullPosition pointingPos;
		block::FullPosition newPos;

		glm::mat4 chunkPos;
		MainGameWPtr mainGame;

	public:
		explicit SelectedBlock(MainGamePtr& mainGame);
		~SelectedBlock() override;

		void update();
	};
}
