#pragma once

#include <string>
#include <iostream>

#include "src/_classdef.h"

namespace engine {


	class exception : std::exception {
	private:
		std::string msg;

		explicit exception() : msg("") {}

	public:

		explicit exception(std::string &msg1) : msg(msg1) {};

		explicit exception(const char *msg1) : msg(msg1) {};

		const char *what() const noexcept override {
			return msg.c_str();
		};
	};
}
