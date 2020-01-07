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
	int line;

public:

	ZprException(const char *file, int line, std::string &msg) : file(file), line(line), msg(msg) {};

	ZprException(const char *file, int line, const char *msg) : file(file), line(line), msg(msg) {};

	ZprException(const char *file, int line, char *msg) : file(file), line(line), msg(msg) {};

	const std::string& getFile() const {
		return file;
	}

	const int& getLine() const {
		return line;
	}

	const char *what() const noexcept override {
		return msg.c_str();
	};
};

#define zprException(what) ZprException(__FILE__, __LINE__, what)