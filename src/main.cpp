#include "mainWin.h"

int main(int argc, char *argv[]) {
	engine::Resources::setExecutablePath(argv[0]);
	try {

		auto window = std::make_shared<MainWindow>();
		window->open();

		return 0;
	} catch (ZprException &e) {
		logger.err(e.what());
	}
}