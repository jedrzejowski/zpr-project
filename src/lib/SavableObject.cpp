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

