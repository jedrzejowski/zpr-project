#pragma once

#include "src/_classdef.h"
#include "json.hpp"


using json = nlohmann::json;

class JsonFile {
private:
	json data = {};
	std::string path;

	explicit JsonFile();
public:

	static const std::string &getConfigDir();

	static JsonFile *load(std::string path);
	static JsonFile *create(std::string path);

	void save();

	bool has(const std::string &key) const;

	bool getBoolean(const std::string &key) const;
	void setBoolean(const std::string &key, const bool &value);

	int getInt(const std::string &key) const;
	void setInt(const std::string &key, const int &value) const;

	std::string getString(const std::string &key) const;
};


