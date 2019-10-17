#include <iostream>

#include "src/game/gamewin.h"
#include "logger.h"

int main() {

	auto window = new GameWin();
	window->open();
	return 0;
}