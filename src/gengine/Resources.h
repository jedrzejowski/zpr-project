#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "_classdef.h"

namespace gengine {
	class Resources {
	private:
		std::vector<std::string> roots;

		std::map<std::string, Texture*> textures;
	public:

		std::string absPath(const std::string &path);

		void load(std::string &path);

		std::string loadTextFile(const std::string &path);

		static Resources &get();

		const Texture *getTexture(std::string path);
	};
}
