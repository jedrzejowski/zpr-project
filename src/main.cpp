#include "src/game/gameWin.h"

int main() {
	try {
		auto window = new game::MainWindow();
		window->open();
		return 0;
	} catch (ZprException& e) {
		logger.err(e.what());
	}
}