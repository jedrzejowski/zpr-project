#pragma once

#include <string>
#include <iostream>
#include <string>
#include <ctime>

//https://stackoverflow.com/questions/9158150/colored-output-in-c
#define TTY_COLOR_RESET   "\033[0m"
#define TTY_COLOR_BLACK   "\033[30m"      /* Black */
#define TTY_COLOR_RED     "\033[31m"      /* Red */
#define TTY_COLOR_GREEN   "\033[32m"      /* Green */
#define TTY_COLOR_YELLOW  "\033[33m"      /* Yellow */
#define TTY_COLOR_BLUE    "\033[34m"      /* Blue */
#define TTY_COLOR_MAGENTA "\033[35m"      /* Magenta */
#define TTY_COLOR_CYAN    "\033[36m"      /* Cyan */
#define TTY_COLOR_WHITE   "\033[37m"      /* White */
#define TTY_COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define TTY_COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define TTY_COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define TTY_COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define TTY_COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define TTY_COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define TTY_COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define TTY_COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define logger (Logger(__FILE__, __LINE__))
//#define fastLog(var) (logger.log(#var).log("=").log(var))

//#define logger //

class Logger {
public:
	Logger(const char *file, int line) {
		std::cout << "[ " << currentDateTime() << " @ " << file << ":" << line << " ]";
	}

	~Logger() {
		std::cout << TTY_COLOR_RESET << std::endl;
	}

	std::string currentDateTime() {
		//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

		return buf;
	}

	template<typename T>
	Logger &msg(const T &obj, const std::string &color = TTY_COLOR_RESET) {

		std::cout << " " << color << obj << TTY_COLOR_RESET;

		return *this;
	}

	template<typename T>
	Logger &err(const T &obj) {
		return msg(obj, TTY_COLOR_RED);
	}

	template<typename T>
	Logger &warn(const T &obj) {
		return msg(obj, TTY_COLOR_YELLOW);
	}

	template<typename T>
	Logger &info(const T &obj) {
		return msg(obj, TTY_COLOR_CYAN);
	}

	template<typename T>
	Logger &log(const T &obj) {
		return msg(obj, TTY_COLOR_WHITE);
	}

	Logger &enter() {
		std::cout << std::endl;
		return *this;
	}
};
