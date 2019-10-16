//
// Created by adam on 16.10.2019.
//

#include "logger.h"

#include <iostream>
#include <string>
#include <time.h>


Logger::Logger() {
}


//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d ⏲ %X", &tstruct);

	return buf;
}

void Logger::msg(const std::string &str, const std::string &color) {
	std::cout << color
			  << "[ " << currentDateTime() << " ] "
			  << str
			  << TTY_COLOR_RESET << std::endl;
}

void Logger::err(const std::string &str) {
	msg(str, TTY_COLOR_RED);
}

void Logger::warn(const std::string &str) {
	msg(str, TTY_COLOR_YELLOW);
}

void Logger::info(const std::string &str) {
	msg(str, TTY_COLOR_CYAN);
}
void Logger::log(const std::string &str) {
	msg(str, TTY_COLOR_WHITE);
}
