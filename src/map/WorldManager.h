#pragma once

#include "_classdef.h"
#include "World.h"

namespace map {
	class WorldManager {
	private:
		std::map<std::string, WorldWPtr> worlds_map;
		std::mutex worlds_mutex;
		std::vector<std::string> all_code_names;

		explicit WorldManager();
		void updateCodeNames();
	public:
		static WorldManager &get();

		static boost::filesystem::path getWorldsDirectory();

		WorldPtr newWorld();
		WorldPtr openWorld(const std::string &code_name);
		WorldPtr deleteWorld(const std::string &code_name);
		[[nodiscard]] const std::vector<std::string> &getAllCodeNames() const;
	};
}


