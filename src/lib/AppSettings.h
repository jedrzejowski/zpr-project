/**
 * @file AppSettings.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include "_classdef.h"
#include "LiveData.hpp"
#include "lib/json.hpp"

using json = nlohmann::json;

/**
 * @brief Odpowiada za ustawienia użytkownika o raz zapis wszystkich plików *.json
 */
class AppSettings {
private:
	AppSettings();
	boost::filesystem::path cfg_dir;

	json toJSON();
	void fromJSON(json &json_obj);
	void initDefaults();
public:
	AppSettings(const AppSettings &) = delete;
	void operator=(const AppSettings &) = delete;

	~AppSettings();

	static AppSettings &get();

	[[nodiscard]] boost::filesystem::path getCfgDir();

	[[nodiscard]] json loadJSON(boost::filesystem::path path);
	void saveJSON(boost::filesystem::path path, const json& content);

	//region SavableObject
	//endregion

	//region Settings
	const LiveData<float> playerCameraAngle;
	const LiveData<float> chunkRenderDistance;
	//endregion
};


