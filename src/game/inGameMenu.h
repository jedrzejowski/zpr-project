#pragma once

#include "src/_classdef.h"
#include "src/lib/object.h"
#include "src/gui/GUI.h"

namespace game {
	class InGameMenu : public engine::Abs3DObj {
	private:
		GameScene *scene;
		engine::Shader* shader;

		gui::Button* button;
	public:
		explicit InGameMenu(GameScene *scene);

	public:
		void render(engine::Scene *scene) override;
	};
}
