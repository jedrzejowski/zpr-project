/**
 * @file Logger.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <src/block/Block.h>
#include "Logger.h"

/**
 * Globalny mutex jest po to aby było można synchronizować linie w wielu wątkach.
 * Zabiezpiecza to przed wpisaniem wielu lini w jednej linii.
 */
std::mutex mutex = std::mutex();

#ifdef IS_TESTING_SCOPE
int Logger::VisibleLogLevel = 5;
#else
int Logger::VisibleLogLevel = 3;
#endif


Logger::Logger(const char *file, int line, int level) : level(level) {
	if (isVisible()) return;
	mutex.lock();

	static auto filename_offset = boost::filesystem::path(__FILE__)
										  .parent_path() // ./src
										  .parent_path() // ./
										  .string()
										  .size() + 1; // ostatni slash;

	std::cout << "[ " << currentDateTime() << " @ " << file + filename_offset << ":" << line << " ]";
}

Logger::~Logger() {
	if (isVisible()) return;
	std::cout << ConsoleColor::RESET << std::endl << std::flush;
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

#ifdef __linux__
//https://stackoverflow.com/questions/9158150/colored-output-in-c
namespace ConsoleColor {
	Type RESET = "\033[0m";
	Type BLACK = "\033[30m";
	Type RED = "\033[31m";
	Type GREEN = "\033[32m";
	Type YELLOW = "\033[33m";
	Type BLUE = "\033[34m";
	Type MAGENTA = "\033[35m";
	Type CYAN = "\033[36m";
	Type WHITE = "\033[37m";
	Type BOLD_BLACK = "\033[1m\033[30m";
	Type BOLD_RED = "\033[1m\033[31m";
	Type BOLD_GREEN = "\033[1m\033[32m";
	Type BOLD_YELLOW = "\033[1m\033[33m";
	Type BOLD_BLUE = "\033[1m\033[34m";
	Type BOLD_MAGENTA = "\033[1m\033[35m";
	Type BOLD_CYAN = "\033[1m\033[36m";
	Type BOLD_WHITE = "\033[1m\033[37m";
}
#elif defined(WIN32)
namespace ConsoleColor {
	Type RESET = "";
	Type BLACK = "";
	Type RED = "";
	Type GREEN = "";
	Type YELLOW = "";
	Type BLUE = "";
	Type MAGENTA = "";
	Type CYAN = "";
	Type WHITE = "";
	Type BOLD_BLACK = "";
	Type BOLD_RED = "";
	Type BOLD_GREEN = "";
	Type BOLD_YELLOW = "";
	Type BOLD_BLUE = "";
	Type BOLD_MAGENTA = "";
	Type BOLD_CYAN = "";
	Type BOLD_WHITE = "";
}
#endif
