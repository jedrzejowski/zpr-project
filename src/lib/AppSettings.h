/**
 * @file AppSettings.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include "_classdef.h"

class AppSettings {
	AppSettings();
	boost::filesystem::path cfgDir;
public:
	AppSettings(const AppSettings &) = delete;
	void operator=(const AppSettings &) = delete;

	~AppSettings();

	static AppSettings &get();

	[[nodiscard]] boost::filesystem::path getCfgDir();

	[[nodiscard]] std::string loadFile(boost::filesystem::path);
	void saveFile(boost::filesystem::path, std::string content);

	[[nodiscard]] json loadJSON(boost::filesystem::path path);
	void saveJSON(boost::filesystem::path path, json content);
};


