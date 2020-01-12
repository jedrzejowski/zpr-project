/**
 * @file Logger.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Block.h>
#include "Logger.h"

/**
 * Globalny mutex jest po to aby było można synchronizować linie w wielu wątkach.
 * Zabiepiecza to przed wpisanie lini w linie.
 */
std::mutex mutex = std::mutex();

int Logger::VisibleLogLevel = 3;

Logger::Logger(const char *file, int line, int level) : level(level) {
	if (isVisible()) return;
	mutex.lock();
	std::cout << "[ " << currentDateTime() << " @ " << file << ":" << line << " ]";
}

Logger::~Logger() {
	if (isVisible()) return;
	std::cout << TTY_COLOR_RESET << std::endl << std::flush;
	mutex.unlock();
}

std::string Logger::currentDateTime() {
	//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	time_t now = time(0);
	struct tm tstruct{};
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

bool Logger::isVisible() {
	return VisibleLogLevel < level;
}
