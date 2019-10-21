#pragma once

#include "src/_classdef.h"
#include "src/gengine/gEngine.h"

namespace game {
	class MainWindow : public engine::Window {
	public:
		void initObjects() override;
		std::string getTitle() override;
	};
}
