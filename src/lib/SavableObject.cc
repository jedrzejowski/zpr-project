/**
 * @file SavableObject.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <filesystem>
#include "SavableObject.h"

bool SavableObject::isNeedSave() const {
	return need_save;
}

void SavableObject::setNeedSave(bool needSave) {
	need_save = needSave;
}

void SavableObject::saveObjectToFile() {
	static auto &app_settings = AppSettings::get();

	if (isNeedSave() && !isDeleted()) {
		app_settings.saveJSON(getSavePath(), toJSON());
		setNeedSave(false);
	}
}

void SavableObject::loadObjectFromFile(const std::function<void()> &onFailed) {
	static auto &app_settings = AppSettings::get();
	std::filesystem::path path;

	try {

		path = getSavePath();
		auto json_data = app_settings.loadJSON(path);

		need_save = false;
		acceptState(json_data);

	} catch (FileInputException &exception) {

		logger(0).err("Error occurred while parsing data from file:").enter().err(path);

		onFailed();

	} catch (WrongJsonException &exception) {

		logger(0).err("Error occurred while reading file:").enter().err(path);

		onFailed();

	} catch (std::exception &exception) {

		logger(0).err("Fatal error occurred while reading file:").enter().err(path);

		onFailed();

	}
}

bool SavableObject::hasSavedFile() {
	return std::filesystem::exists(getSavePath());
}

json &SavableObject::assertGetNumber(json &maybe_number) {
	if (maybe_number.is_number())
		return maybe_number;
	else throw WrongJsonException();
}

glm::vec3 SavableObject::assertGetVec3(json &maybe_vector) {
	if (!maybe_vector.is_array() || maybe_vector.size() != 3)
		throw WrongJsonException();

	return glm::vec3(
			assertGetNumber(maybe_vector[0]),
			assertGetNumber(maybe_vector[1]),
			assertGetNumber(maybe_vector[2])
	);
}

std::string SavableObject::assertGetString(json &maybe_string) {
	if (maybe_string.is_string())
		return maybe_string;
	else throw WrongJsonException();
}

bool SavableObject::isDeleted() const {
	return is_deleted;
}

void SavableObject::deleteThisObjectAsFile() {
	is_deleted = true;

}

