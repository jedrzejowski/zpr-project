/**
 * @file Exception.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <string>
#include <iostream>
#include <boost/filesystem/path.hpp>
#include "Logger.h"

/**
 * @brief Wyjątek ogólny
 */
class ZprException : std::exception {
private:
	std::string msg;
	std::string file;
	std::string where;
	int line;

public:

	ZprException(const char *file, int line, const char *where, std::string &msg) :
			where(where), file(file), line(line), msg(msg) {
		logger(1).err("ZprException(): creating at").log(file).log(line);
	};

	ZprException(const char *file, int line, const char *where, const char *msg) :
			where(where), file(file), line(line), msg(msg) {
		logger(1).err("ZprException(): creating at").log(file).log(line);
	};

	ZprException(const char *file, int line, const char *where, char *msg) :
			where(where), file(file), line(line), msg(msg) {
		logger(1).err("ZprException(): creating at").log(file).log(line);
	};

	[[nodiscard]] const std::string &getFile() const {
		return file;
	}

	[[nodiscard]] const int &getLine() const {
		return line;
	}

	[[nodiscard]] const char *what() const noexcept override {
		return msg.c_str();
	};
};

/**
 * @brief Wyjątek dla błędu wczytywania pliku
 */
class FileInputException : public std::exception {
private:
	std::string file;
public:
	explicit FileInputException(const char *file) : file(file) {};
	explicit FileInputException(std::string &file) : file(file) {};
	explicit FileInputException(boost::filesystem::path &file) : file(file.string()) {};

	[[nodiscard]] const std::string &getFile() const {
		return file;
	}
};

/**
 * @brief Wyjątek dla błędu zapisywania pliku
 */
class FileOutputException : public std::exception {
private:
	std::string file;
public:
	explicit FileOutputException(const char *file) : file(file) {};
	explicit FileOutputException(std::string &file) : file(file) {};
	explicit FileOutputException(boost::filesystem::path &file) : file(file.string()) {};

	[[nodiscard]] const std::string &getFile() const {
		return file;
	}
};

/**
 * @brief Wyjątek dla błędu złego pliku json
 */
class WrongJsonException : public std::exception {
};

/**
 * @brief Makro do tworzenia głównej klasy wyjątku
 */
#define zprException(where, what) ZprException(__FILE__, __LINE__, where, what)