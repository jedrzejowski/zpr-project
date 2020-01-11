/**
 * @file Resources.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

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

		std::map<std::string, TexturePtr> textures;
	public:

		boost::filesystem::path absPath(const std::string &path);

		std::string loadTextFile(std::string path);

		static Resources &get();

		TexturePtr getTexture(std::string path);

		static void setExecutablePath(char *path);
	};
}
