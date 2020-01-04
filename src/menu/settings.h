#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

namespace menu {

	class SettingsScene : public engine::Scene {
	public:
		void render(engine::WindowPtr window) override;
	};
}