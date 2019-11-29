#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/filesystem.hpp>

#include "src/_classdef.h"

namespace engine {
	class Resources {
	private:
		std::vector<std::string> roots;

		std::map<std::string, Texture *> textures;
	public:

		boost::filesystem::path absPath(const std::string &path);

		void load(std::string &path);

		std::string loadTextFile(const std::string &path);

		static Resources &get();

		const Texture *getTexture(std::string path);

		static void setExecutablePath(char *path);
	};
}
