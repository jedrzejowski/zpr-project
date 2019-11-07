#pragma once

#include "src/_classdef.h"
#include "src/engine/Engine.h"

class MainWindow : public engine::Window {
public:
	void initObjects() override;
	std::string getTitle() override;
};

