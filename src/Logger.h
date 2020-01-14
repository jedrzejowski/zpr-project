/**
 * @file Logger.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <string>
#include <iostream>
#include <string>
#include <ctime>
#include <mutex>

/**
 * @brief Namespace dla kolorów konsoli
 */
namespace ConsoleColor {
	typedef const char *Type;

	extern Type RESET;
	extern Type BLACK;
	extern Type RED;
	extern Type GREEN;
	extern Type YELLOW;
	extern Type BLUE;
	extern Type MAGENTA;
	extern Type CYAN;
	extern Type WHITE;
	extern Type BOLD_BLACK;
	extern Type BOLD_RED;
	extern Type BOLD_GREEN;
	extern Type BOLD_YELLOW;
	extern Type BOLD_BLUE;
	extern Type BOLD_MAGENTA;
	extern Type BOLD_CYAN;
	extern Type BOLD_WHITE;
}

/**
 * @brief Klasa zajmująca się tworzeniem logów w czasie działania programu
 *
 * Przy używaniu loggera należy używać makra "logger(x)"
 */
class Logger {
private:
	int level;

	bool isVisible();
public:
	static int VisibleLogLevel;

	Logger(const char *file, int line, int level);
	~Logger();


	std::string currentDateTime();

	template<typename T>
	inline Logger &msg(const T &obj, ConsoleColor::Type color = ConsoleColor::RESET) {
		if (isVisible()) return *this;

		std::cout << " " << color << obj << ConsoleColor::RESET;

		return *this;
	}

	template<typename T>
	inline Logger &err(const T &obj) {
		return msg(obj, ConsoleColor::RED);
	}

	template<typename T>
	inline Logger &warn(const T &obj) {
		return msg(obj, ConsoleColor::YELLOW);
	}

	template<typename T>
	inline Logger &info(const T &obj) {
		return msg(obj, ConsoleColor::CYAN);
	}

	template<typename T>
	inline Logger &log(const T &obj) {
		return msg(obj, ConsoleColor::WHITE);
	}

	inline Logger &enter() {
		std::cout << std::endl;
		return *this;
	}

	template<typename T>
	inline Logger &constructor(const T *obj) {
		return msg(std::string("") + typeid(obj).name() + "()").log(obj);
	}

	template<typename T>
	inline Logger &destructor(const T *obj) {
		return msg(std::string("~") + typeid(obj).name() + "()").log(obj);
	}
};

/**
 * @brief Przy używaniu loggera należy używać makra
 */
#define logger(level) (Logger(__FILE__, __LINE__, level))