#include <src/lib/jsonFile.h>
#include "mainWin.h"

int main() {
	try {

		logger.log(JsonFile::getConfigDir());

//		auto window = new MainWindow();
//		window->open();

		return 0;
	} catch (ZprException &e) {
		logger.err(e.what());
	}
}