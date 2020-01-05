//
// Created by adam on 08.11.2019.
//

#include <fstream>
#include <iomanip>
#include <boost/filesystem/operations.hpp>
#include "appSettings.h"
#include "cfgpath.h"

AppSettings::AppSettings() {
	logger.constructor(this);

	{
		char temp[256];
		get_user_config_folder(temp, sizeof(temp), "ZprCraft");
		cfgDir = temp[0] == 0 ? "." : temp;
	}
}

AppSettings &AppSettings::get() {
	static AppSettings as;
	return as;
}

std::string AppSettings::loadFile(boost::filesystem::path path) {
	return std::string();
}

void AppSettings::saveFile(boost::filesystem::path path, std::string content) {
}

boost::filesystem::path AppSettings::getCfgDir() {
	return cfgDir;
}

json AppSettings::loadJSON(boost::filesystem::path path) {

	std::ifstream fileStream(path);

	if (!fileStream.is_open())
		throw zprException("cant read file");

	json data;
	fileStream >> data;
	fileStream.close();

	return data;
}

void AppSettings::saveJSON(boost::filesystem::path path, json content) {
	boost::filesystem::create_directories(path.parent_path());

	std::ofstream fileStream(path);

	if (!fileStream.is_open())
		throw zprException("cant write file");

	fileStream << std::setw(4) << content << std::endl;
}
