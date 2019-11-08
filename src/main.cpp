#include "mainWin.h"

int main() {
	try {
		auto* ii = new engine::InputInterface();
		ii->dumpParentTree();
		delete ii;

//		auto window = new MainWindow();
//		window->open();
		return 0;
	} catch (ZprException& e) {
		logger.err(e.what());
	}
}