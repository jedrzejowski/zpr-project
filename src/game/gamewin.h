#pragma once

#include "src/gengine/gEngine.h"

class GameWin : public gengine::Window {
public:
	void initObjects() override;
	std::string getTitle() override;
};
