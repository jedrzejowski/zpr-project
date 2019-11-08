#include "mainWin.h"

int main() {
	try {

		auto window = new MainWindow();
		window->open();
		return 0;

	} catch (ZprException& e) {
		logger.err(e.what());
	}
}