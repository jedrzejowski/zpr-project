#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

namespace gui {
	class Button : public engine::Abs3DObj {
	protected:
		const engine::Texture* texture;
		std::string label;
	public:
		Button();
		void render(engine::Scene *scene) override;
	};
}
