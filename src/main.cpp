/**
 * @file main.cpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

/**
 *
 */

#include "MainWindow.h"

int main(int argc, char *argv[]) {

	try {

		engine::Resources::setExecutablePath(argv[0]);

		auto window = std::make_shared<MainWindow>();
		window->open();

		return 0;
	} catch (ZprException &e) {

		std::cerr << "fatal ZprException occurred" << std::endl;
		std::cerr << e.what();

		return 1;
	} catch (std::exception &e) {

		std::cerr << "fatal std::exception occurred" << std::endl;
		std::cerr << e.what();

		return 1;
	}

}