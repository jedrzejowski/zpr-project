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
#include <filesystem>

#include "src/_classdef.h"

namespace engine {

	/**
	 * @brief Singleton odpowiadający za ładowanie tekstur i shaderów
	 */
	class Resources {
	private:

		std::map<std::string, TexturePtr> textures;
	public:

		std::filesystem::path absPath(const std::string &path);

		std::string loadTextFile(std::string path);

		static Resources &get();

		TexturePtr getTexture(std::string path);

		static void setExecutablePath(char *path);
	};
}
