/**
 * @file Exception.hpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <string>
#include <iostream>

class ZprException : std::exception {
private:
	std::string msg;
	std::string file;
	std::string where;
	int line;

public:

	ZprException(const char *file, int line, const char *where, std::string &msg) :
			where(where), file(file), line(line), msg(msg) {};

	ZprException(const char *file, int line, const char *where, const char *msg) :
			where(where), file(file), line(line), msg(msg) {};

	ZprException(const char *file, int line, const char *where, char *msg) :
			where(where), file(file), line(line), msg(msg) {};

	const std::string &getFile() const {
		return file;
	}

	const int &getLine() const {
		return line;
	}

	const char *what() const noexcept override {
		return msg.c_str();
	};
};

#define zprException(where, what) ZprException(__FILE__, __LINE__, where, what)