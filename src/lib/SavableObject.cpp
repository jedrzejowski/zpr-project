/**
 * @file SavableObject.cpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <boost/filesystem/operations.hpp>
#include "SavableObject.h"

bool SavableObject::isNeedSave() const {
	return need_save;
}

void SavableObject::setNeedSave(bool needSave) {
	need_save = needSave;
}

void SavableObject::saveObjectToFile() const {
	static auto &app_settings = AppSettings::get();

	if (isNeedSave()) {
		app_settings.saveJSON(getSavePath(), toJSON());
	}
}

void SavableObject::loadObjectFromFile() {
	static auto &app_settings = AppSettings::get();

	auto json_data = app_settings.loadJSON(getSavePath(app_settings));

	need_save = false;
	acceptState(json_data);
}

bool SavableObject::hasSavedFile() {
	return boost::filesystem::exists(getSavePath());
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

