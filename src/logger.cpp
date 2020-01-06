#include <src/block/block.h>
#include "logger.h"

std::mutex mutex = std::mutex();

Logger::Logger(const char *file, int line) {
	mutex.lock();
	std::cout << "[ " << currentDateTime() << " @ " << file << ":" << line << " ]";
}

Logger::~Logger() {
	std::cout << TTY_COLOR_RESET << std::endl << std::flush;
	mutex.unlock();
}
std::string Logger::currentDateTime() {
	//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}