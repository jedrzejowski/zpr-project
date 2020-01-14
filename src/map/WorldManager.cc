/**
 * @file WorldManager.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <filesystem>
#include "WorldManager.h"
#include "World.h"

map::WorldManager::WorldManager() {
	updateCodeNames();
}

map::WorldManager &map::WorldManager::get() {
	static WorldManager world_manager;
	return world_manager;
}

std::filesystem::path map::WorldManager::getWorldsDirectory() {
	return AppSettings::get().getCfgDir() / "worlds";
}

map::WorldPtr map::WorldManager::newWorld() {
	std::lock_guard<std::mutex> lock(worlds_mutex);

	auto base_dir = getWorldsDirectory();

	map::WorldPtr world_ptr;

	for (int i = 0; true; i++) {
		auto code_name = std::string("default") + std::to_string(i);

		if (std::filesystem::is_directory(base_dir / code_name)) continue;


		world_ptr = map::World::create(code_name);
		worlds_map[code_name] = world_ptr;
		world_ptr->setDisplayName(std::string("Swiat ") + std::to_string(i));
		world_ptr->fullSave();

		break;
	}

	updateCodeNames();

	return world_ptr;
}

map::WorldPtr map::WorldManager::openWorld(const std::string &code_name) {
	std::lock_guard<std::mutex> lock(worlds_mutex);

	if (auto world_ptr = worlds_map[code_name].lock()) {
		logger(0).log(code_name).log("counts").log(world_ptr.use_count());
		return world_ptr;
	} else {
		world_ptr = map::World::create(code_name);
		worlds_map[code_name] = world_ptr;
		world_ptr->fullSave();
		updateCodeNames();

		logger(0).log(code_name).log("counts").log(world_ptr.use_count());
		return world_ptr;
	}
}

const std::vector<std::string> &map::WorldManager::getAllCodeNames() const {
	return all_code_names;
}

void map::WorldManager::updateCodeNames() {
	logger(0).log("udpating");
	all_code_names.clear();

	if (!std::filesystem::is_directory(getWorldsDirectory()))
		std::filesystem::create_directories(getWorldsDirectory());

	for (auto iterator = std::filesystem::directory_iterator(getWorldsDirectory());
		 iterator != std::filesystem::directory_iterator{}; iterator++) {

		auto code_name = iterator->path().filename().string();
		all_code_names.push_back(code_name);
	}
}

void map::WorldManager::deleteWorld(const std::string &code_name) {
	auto world_ptr = openWorld(code_name);
	std::lock_guard<std::mutex> lock(worlds_mutex);

	world_ptr->deleteThisObjectAsFile();
	worlds_map.erase(code_name);

	std::filesystem::remove_all(getWorldsDirectory() / code_name);
	updateCodeNames();
}

map::WorldPtr map::WorldManager::clearWorld(const std::string &code_name) {
	auto world_ptr = openWorld(code_name);
	std::lock_guard<std::mutex> lock(worlds_mutex);

	world_ptr->chunks.clear();

	std::filesystem::remove_all(getWorldsDirectory() / code_name / "surface1");
	return world_ptr;
}

