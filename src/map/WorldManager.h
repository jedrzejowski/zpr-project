/**
 * @file WorldManager.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "World.h"

namespace map {

	/**
	 * @brief Manager chunk'ów
	 *
	 * Nie jest dobrym, aby powstało wiele obiektów World do tego samego świata, z uwagi na to, że te obiekty
	 * posiadają reprezentacje w plikach, więc utworzenie ich miało by fatalne skutki, dlatego ta klasa, odpowiada, za
	 * zarządzanie dostępnością obiektów World
	 */
	class WorldManager {
	private:
		std::map<std::string, WorldWPtr> worlds_map;
		std::mutex worlds_mutex;
		std::vector<std::string> all_code_names;

		explicit WorldManager();
		void updateCodeNames();
	public:
		static WorldManager &get();

		static std::filesystem::path getWorldsDirectory();

		WorldPtr newWorld();
		WorldPtr openWorld(const std::string &code_name);
		void deleteWorld(const std::string &code_name);
		WorldPtr clearWorld(const std::string &code_name);
		[[nodiscard]] const std::vector<std::string> &getAllCodeNames() const;
	};
}


