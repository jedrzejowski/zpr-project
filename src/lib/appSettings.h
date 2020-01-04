#pragma once

#include <boost/filesystem/path.hpp>
#include "_classdef.h"

class AppSettings {
	AppSettings();
	boost::filesystem::path cfgDir;
public:

	static AppSettings& get();

	boost::filesystem::path getCfgDir();

	std::string loadFile(boost::filesystem::path);
	void saveFile(boost::filesystem::path, std::string content);

	json loadJSON(boost::filesystem::path path);
	void saveJSON(boost::filesystem::path path, json content);
};


