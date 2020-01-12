/**
 * @file AppSettings.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <fstream>
#include <iomanip>
#include <boost/filesystem/operations.hpp>
#include "AppSettings.h"
#include "SavableObject.h"
#include "cfgpath.h"

const char *SETTINGS_FILENAME = "settings";

AppSettings::AppSettings() :
		playerCameraAngle(0),
		chunkRenderDistance(0) {
	logger(4).constructor(this);

	char temp[256];
	get_user_config_folder(temp, sizeof(temp), global::AppName.c_str());
	cfg_dir = temp[0] == 0 ? "." : temp;

	try {
		auto json_obj = loadJSON(cfg_dir / SETTINGS_FILENAME);
		fromJSON(json_obj);
	} catch (std::exception &) {
		initDefaults();
	}
}

AppSettings::~AppSettings() {
	logger(4).destructor(this);

	try {
		saveJSON(cfg_dir / SETTINGS_FILENAME, toJSON());
	} catch (FileOutputException &exception) {
		logger(0).err("Fatal error occurred while saving to file:").enter().err(exception.getFile());
	}
}

const char *JSON_ATTR_PLAYER_CAMERA_ANGLE = "playerCameraAngle";
const char *JSON_ATTR_CHUNK_RENDER_DISTANCE = "chunkRenderDistance";

AppSettings &AppSettings::get() {
	static AppSettings as;
	return as;
}

json AppSettings::toJSON() {
	json json_obj;

	json_obj[JSON_ATTR_PLAYER_CAMERA_ANGLE] = playerCameraAngle.get();
	json_obj[JSON_ATTR_CHUNK_RENDER_DISTANCE] = chunkRenderDistance.get();

	return json_obj;
}

void AppSettings::fromJSON(json &json_obj) {
	playerCameraAngle.set(SavableObject::assertGetNumber(json_obj[JSON_ATTR_PLAYER_CAMERA_ANGLE]));
	chunkRenderDistance.set(SavableObject::assertGetNumber(json_obj[JSON_ATTR_CHUNK_RENDER_DISTANCE]));
}

void AppSettings::initDefaults() {
	playerCameraAngle.set(45.0f);
	chunkRenderDistance.set(4.0f);
}


boost::filesystem::path AppSettings::getCfgDir() {
	return cfg_dir;
}

json AppSettings::loadJSON(boost::filesystem::path path) {

	std::ifstream fileStream(path.string());

	if (!fileStream.is_open())
		throw FileInputException(path);

	json data;
	fileStream >> data;
	fileStream.close();

	return data;
}

void AppSettings::saveJSON(boost::filesystem::path path, json content) {
	boost::filesystem::create_directories(path.parent_path());

	std::ofstream fileStream(path.string());

	if (!fileStream.is_open())
		throw FileOutputException(path);

	fileStream
//			<< std::setw(4) // ładne formatowanie
			<< content
			<< std::endl;
}

