#include <fstream>
#include <iomanip>
#include "jsonFile.h"
#include "cfgpath.h"


JsonFile::JsonFile() {
}


JsonFile *JsonFile::load(std::string path) {
	auto *file = create(path);

	path = getConfigDir() + path;
	std::ifstream fileStream(path);

	if (!fileStream.is_open())
		throw zprException("cant read file");

	// taki ficzer biblioteki
	fileStream >> file->data;

	fileStream.close();

	return file;
}

JsonFile *JsonFile::create(std::string path) {
	path = getConfigDir() + path;
	auto *file = new JsonFile();
	file->path = path;

	return file;
}


void JsonFile::save() {
	std::ofstream fileStream(path);

	if (!fileStream.is_open())
		throw zprException("cant write file");

	logger.log(path);
	// taki ficzer biblioteki
	fileStream << std::setw(4) << data << std::endl;
}

const std::string &JsonFile::getConfigDir() {
	static std::string cfgDir;

	if (cfgDir.empty()) {

		char temp[MAX_PATH];
		get_user_config_folder(temp, sizeof(temp), AppName.c_str());
		if (temp[0] == 0)
			throw zprException("error while getting user config path");

		cfgDir = temp;
	}

	return cfgDir;
}


bool JsonFile::has(const std::string &key) const {
	return data.contains(key);
}

bool JsonFile::getBoolean(const std::string &key) const {
	auto value = data[key];

	if (value.is_boolean())
		return value;

	throw zprException("wrong type");
}

void JsonFile::setBoolean(const std::string &key, const bool &value) {
	data[key] = value;
}

int JsonFile::getInt(const std::string &key) const {
	auto value = data[key];

	if (value.is_number_integer())
		return value;

	throw zprException("wrong type");
}

void JsonFile::setInt(const std::string &key, const int &value) const {
}