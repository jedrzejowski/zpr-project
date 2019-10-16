#pragma once

#include <string>

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

class Logger {
private:
	Logger();
public:
	static Logger &get() {
		static Logger logger = Logger();
		return logger;
	}
	void msg(const std::string &str, const std::string &color = TTY_COLOR_RESET);
	void err(const std::string &str);
	void warn(const std::string &str);
	void info(const std::string &str);
	void log(const std::string &str);
};


