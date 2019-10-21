#pragma once

#include "src/gengine/gEngine.h"

class GameWin : public engine::Window {
public:
	void initObjects() override;
	std::string getTitle() override;
};
