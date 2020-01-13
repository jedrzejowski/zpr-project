/**
 * @file AppSettings.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <filesystem>
#include "_classdef.h"
#include "LiveData.hpp"


class AppSettings {
private:
	AppSettings();
	std::filesystem::path cfg_dir;

	json toJSON();
	void fromJSON(json &json_obj);
	void initDefaults();
public:
	AppSettings(const AppSettings &) = delete;
	void operator=(const AppSettings &) = delete;

	~AppSettings();

	static AppSettings &get();

	[[nodiscard]] std::filesystem::path getCfgDir();

	[[nodiscard]] json loadJSON(std::filesystem::path path);
	void saveJSON(std::filesystem::path path, json content);

	//region SavableObject
	//endregion

	//region Settings
	const LiveData<float> playerCameraAngle;
	const LiveData<float> chunkRenderDistance;
	//endregion
};


