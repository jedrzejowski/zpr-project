#pragma once

#include <string>
#include <iostream>


class ZprException : std::exception {
private:
	std::string msg;
	std::string file;
	int line;

public:

	explicit ZprException(const char *file, int line, std::string &msg1) :
			file(file), line(line), msg(msg1) {};

	explicit ZprException(const char *file, int line, const char *msg1) :
			file(file), line(line), msg(msg1) {};

	const char *getFile() const {
		return file.c_str();;
	}

	int getLine() const {
		return line;
	}

	const char *what() const noexcept override {
		return msg.c_str();
	};
};

#define exception(what) ZprException(__FILE__, __LINE__, what)