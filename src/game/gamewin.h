#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

namespace game {
	class MainWindow : public engine::Window {
	public:
		void initObjects() override;
		std::string getTitle() override;
	};
}
