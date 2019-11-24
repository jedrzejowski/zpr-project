#include "jsonFile.h"
#include "cfgpath.h"


JsonFile::JsonFile() {
}


JsonFile *JsonFile::load(const std::string &path) {
	return nullptr;
}

void JsonFile::save(std::string path) {
	if (path.empty()) path = this->path;
}

const std::string &JsonFile::getConfigDir() {
	static std::string cfgDir;

	if (cfgDir.empty()) {

		char temp[MAX_PATH];
		get_user_config_folder(temp, sizeof(temp), "ZprCraft");
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