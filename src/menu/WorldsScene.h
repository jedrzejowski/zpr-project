/**
 * @file WorldsScene.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

namespace menu {
	class WorldsScene : public engine::Scene {
	public:
		void render(engine::WindowPtr& window) override;
	};
}