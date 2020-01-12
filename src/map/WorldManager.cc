//
// Created by adam on 12.01.2020.
//

#include <boost/filesystem/operations.hpp>
#include "WorldManager.h"

map::WorldManager::WorldManager() {
	updateCodeNames();
}

map::WorldManager &map::WorldManager::get() {
	static WorldManager world_manager;
	return world_manager;
}

boost::filesystem::path map::WorldManager::getWorldsDirectory() {
	return AppSettings::get().getCfgDir() / "worlds";
}

map::WorldPtr map::WorldManager::newWorld() {
	std::lock_guard<std::mutex> lock(worlds_mutex);

	auto base_dir = getWorldsDirectory();

	map::WorldPtr world_ptr;

	for (int i = 0; true; i++) {
		auto code_name = std::string("default") + std::to_string(i);

		if (boost::filesystem::is_directory(base_dir.concat(code_name))) continue;

		world_ptr = map::World::create(code_name);
		worlds_map[code_name] = world_ptr;
		world_ptr->setDisplayName(std::string("Swiat ") + std::to_string(i));
		world_ptr->fullSave();

		break;
	}

	return world_ptr;
}

map::WorldPtr map::WorldManager::openWorld(const std::string &code_name) {
	std::lock_guard<std::mutex> lock(worlds_mutex);

	if (auto world_ptr = worlds_map[code_name].lock()) {
		return world_ptr;
	} else {
		world_ptr = map::World::create(code_name);
		worlds_map[code_name] = world_ptr;
		world_ptr->fullSave();
		updateCodeNames();
		return world_ptr;
	}
}

map::WorldPtr map::WorldManager::deleteWorld(const std::string &code_name) {
	return map::WorldPtr();
}

const std::vector<std::string> &map::WorldManager::getAllCodeNames() const {
	return all_code_names;
}

void map::WorldManager::updateCodeNames() {
	all_code_names.clear();

	for (auto iterator = boost::filesystem::directory_iterator(getWorldsDirectory());
		 iterator != boost::filesystem::directory_iterator{}; iterator++) {

		auto code_name = iterator->path().leaf().string();
		all_code_names.push_back(code_name);
	}
}

